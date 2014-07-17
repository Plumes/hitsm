#coding:UTF-8
import sys
import os
import glob
import re
import ctypes
import pdb
import time
import datetime
import json
import string
import shutil
import sim
import random

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import torndb

from tornado.options import define, options
define("port", default=8000, help="run on the given port", type=int)
define("mysql_host", default="127.0.0.1:3306", help="database host")
define("mysql_database", default="DB", help="database name")
define("mysql_user", default="root")
define("mysql_password", default="123456qwe")

class Application(tornado.web.Application):
    """docstring for Application"""
    def __init__(self):
        handlers = [
            (r"/",IndexHandler),
            (r"/problems/query",QuestionQueryHandler),                                                                                                                                                                       
            (r"/problems/choose",QuestionQueryHandler),                                                                                                                                                                       
            (r"/problems/manage/(\w*)",QuestionManageHandler),                                                                                                                                                                       
            (r"/login", LoginHandler),
            (r"/logout", LogoutHandler),
            (r"/captcha/(\w+)", CaptchaHandler),
            (r"/users/generate",GenerateHandler),
            (r"/users/userinfo",UserInfoHandler),
            (r"/users/usertype",UserTypeHandler),
            (r"/judge",JudgeHandler),
            (r'/run',ExamHandler),
            (r'/upload',UpLoadHandler),
            (r'/onLoad', OnLoadHandler),
            (r'/check', CheckHandler),
            (r'/polling',PollHandler),
            (r'/result',ResultHandler),
            (r'/detail_(\d+)_(\d+)_(\d+)',DetailHandler),
            (r'/mark_(\d+)_(\d+)_(\d+)_([12])',MarkHandler),
            (r'/report',ReportHandler),
                #(r"/register", RegisterHandler),
            #(r"/dashboard/", DashboardHandler),
            #(r"/dashboard/settings", SettingsHandler),
        ]
        settings = dict(
            cookie_secret="61oETzKXQAGaYdkL5gEmGeJJFuYh7EQnp2XdTP1o/Vo=",
            site_url="http://192.168.33.10:8080/",
            login_url="/login",
            orgnization = "威海惠光电子系统工程有限公司 ",
            site_name = "代码相似性检测系统",
            template_path = os.path.join(os.path.dirname(__file__),"templates"),
            static_path = os.path.join(os.path.dirname(__file__),"static"),
        )
        tornado.web.Application.__init__(self, handlers, **settings)
        
        self.db = torndb.Connection(
            host = options.mysql_host, database = options.mysql_database,
            user = options.mysql_user, password = options.mysql_password
            )

class BaseHandler(tornado.web.RequestHandler):
    
    def site_url(self):
      return self.application.settings["site_url"]

    @property
    def db(self):
      return self.application.db

    def get_current_user(self):
      user = {}
      user["uname"] = self.get_secure_cookie("uname")
      if self.get_secure_cookie("uid"):
          user["uid"] = int(self.get_secure_cookie("uid"))
      else:
          user["uid"] = 0
      if self.get_secure_cookie("privilege"):
          user["privilege"] = int(self.get_secure_cookie("privilege"))
      else:
          user["privilege"] = 0
      return user

class IndexHandler(BaseHandler):

  def get(self):
    self.render("index.html", user=self.current_user)

class LoginHandler(BaseHandler):

    def get(self):
      self.render("login.html")

    def post(self):
      raw_name = tornado.escape.xhtml_escape(self.get_argument("uname"))
      raw_pwd = tornado.escape.xhtml_escape( self.get_argument("pwd") )
      row =  self.db.get("SELECT USER_ID,USER_PASSWORD,USER_TYPE FROM USER WHERE USER_NAME=\"{0}\"".format(raw_name.encode("UTF-8")))
      if row and row["USER_PASSWORD"] == raw_pwd:
          self.set_secure_cookie("uname", raw_name, expires_days=None)
          self.set_secure_cookie("uid", str(row["USER_ID"]), expires_days=None)
          self.set_secure_cookie("privilege", str(row["USER_TYPE"]), expires_days=None)
          self.set_secure_cookie("captcha","")
          #self.redirect("/")
          err_code = 0;
      else:
          err_code = 1
      login_err_msg = [u"", u"用户名或密码错误", u"该账号尚未激活！"]
      #self.render("login.html", err_msg = LogInHandler.login_err_msg[LogInHandler.err_code])
      self.write( json.dumps({"code":err_code,"msg":login_err_msg[err_code].encode("UTF-8")}) )

class CaptchaHandler(BaseHandler):
  def post(self,oper):
    if oper=="get":
      code = random.randint(1000,10000)
      self.write( json.dumps({"code":0,"msg":code}) )
      self.set_secure_cookie("captcha",str(code),expires_days=None)
    elif oper=="verify":
      r_code =  self.get_argument("code",default="0")
      if r_code == self.get_secure_cookie("captcha"):

        res = 0
      else:
        res = 1
      self.write( json.dumps({"code":res}) ) 


class LogoutHandler(BaseHandler):
  def get(self):
    self.set_secure_cookie("uname", "", expires_days=None)
    self.set_secure_cookie("uid", "", expires_days=None)
    self.set_secure_cookie("privilege", "", expires_days=None)
    self.redirect(self.site_url())

class UserInfoHandler(BaseHandler):
    def get(self):
        if self.current_user["privilege"] <1:
            self.redirect(self.site_url()+"login")
        cur_user = self.db.get("SELECT * FROM USER WHERE USER_ID={0}".format(self.current_user["uid"]))
        self.render("user_info.html", user = self.current_user, cur_user = cur_user)

    def post(self):
      if self.current_user["privilege"] > 1:
        uid = int(self.current_user["uid"])
        new_info = {}
        new_info["NAME"] = self.get_argument("inputName",default="").encode("UTF-8")
        new_info["GENDER"] = self.get_argument("gender",default="").encode("UTF-8")
        new_info["AFFILIATION"] = self.get_argument("inputOffice",default="").encode("UTF-8")
        new_info["EMAIL"] = self.get_argument("inputEmail",default="").encode("UTF-8")
        new_info["PHONE"] = self.get_argument("inputPhone",default="").encode("UTF-8")

        condition="SET "
        for k,v in new_info.iteritems():
          condition = condition + "{0}=\"{1}\",".format(k,v)
        condition = condition[0:-1]

        self.db.execute("UPDATE USER "+ condition + " WHERE USER_ID={0}".format(uid))
        self.redirect("/users/userinfo")

class UserTypeHandler(BaseHandler):

  def get(self):
      if self.current_user["privilege"] <3:
          self.redirect(self.site_url()+"login")
      users = self.db.query("SELECT * FROM USER WHERE USER_TYPE<3")
      self.render("user_type.html", user = self.current_user, users = users)
  def post(self):
      if self.current_user["privilege"] > 2:
          user_type = int(self.get_argument("type",default="1"))
          uid_list = self.get_arguments("uidList[]")
          for uid in uid_list:
              self.db.execute("UPDATE USER SET USER_TYPE={0} WHERE USER_ID={1}".format(user_type,uid))
          self.write(json.dumps({"code":0}))
          
class QuestionManageHandler(BaseHandler):

  def get(self,oper):
    if self.current_user["privilege"] < 2:
      self.redirect(self.site_url()+"login")
    if oper == "new":
      m_category1 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 1")
      m_category2 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 2")
      m_category3 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 3")
      self.render("problem_info.html",user=self.current_user, m_category1=m_category1, m_category2=m_category2, m_category3=m_category3)
    elif oper == "update":
      qid = self.get_argument("qid")
      question = self.db.get("SELECT QUESTION_TITLE,QUESTION_TYPE_NAME FROM QUESTION WHERE QUESTION_ID=\"{0}\"".format(qid))
      self.render("update_problem.html",user=self.current_user,question=question) 
    else:
      if self.current_user["privilege"] in [3]:
        questions = self.db.query("SELECT * FROM QUESTION ORDER BY QUESTION_SUBMIT_DATE DESC")
      else:
        questions = self.db.query("SELECT * FROM QUESTION WHERE USER_ID={0} ORDER BY QUESTION_SUBMIT_DATE DESC".format(self.current_user["uid"]))
      self.render("question_manage.html",user=self.current_user,questions=questions)

  def post(self,oper):
    if self.current_user["privilege"] < 2:
      self.redirect(self.site_url()+"login")
    if oper == "delete":
      qid = (self.get_argument("qid"))
      sql = "DELETE FROM QUESTION WHERE QUESTION_ID=\"{0}\"".format(qid)
      if self.current_user["privilege"] not in [3]:
        sql = sql +  " AND USER_ID={0}".format(self.current_user["uid"])
      print(sql)
      self.db.execute(sql) 
    elif oper=="new":
      category3_id = self.get_argument("category3")
      type_name = self.db.get("SELECT QUESTION_TYPE_NAME FROM QUESTION_TYPE WHERE QUESTION_TYPE_ID=\"{0}\"".format(category3_id))["QUESTION_TYPE_NAME"].encode("UTF-8")
      last_row = self.db.get("SELECT QUESTION_ID FROM QUESTION WHERE QUESTION_TYPE_ID=\"{0}\" ORDER BY QUESTION_ID DESC LIMIT 0,1".format(category3_id))
      if last_row:
        last_id = int(last_row["QUESTION_ID"][-4:])+1
      else:
        last_id = 1
      qid = category3_id +("0"*12)+ "%04d" % last_id
      title = self.get_argument("inputName").encode("UTF-8")
      path=os.path.join(os.path.dirname(__file__),'static/questions')
      file_name = qid+".pdf"
      #print(self.request.files)
      file_metas=self.request.files['file']
      for meta in file_metas:
        with open(os.path.join(path,file_name),"wb") as up:
          up.write(meta["body"])
      sql = "INSERT INTO `QUESTION`(`QUESTION_ID`, `QUESTION_TYPE_ID`, `QUESTION_TYPE_NAME`, `USER_ID`, `USER_NAME`, `QUESTION_TITLE`, `QUESTION_FILE_PATH`, `QUESTION_FILE_NAME`, `QUESTION_SUBMIT_DATE`) "+"VALUES(\"{0}\",\"{1}\",\"{2}\",{3},\"{4}\",\"{5}\",\"{6}\",\"{7}\",NOW())".format(qid,category3_id,type_name,self.current_user["uid"],self.current_user["uname"],title,path,file_name)
      print(sql)
      self.db.execute(sql)
      # self.db.execute("INSERT INTO `QUESTION`(`QUESTION_ID`, `QUESTION_TYPE_ID`, `QUESTION_TYPE_NAME`, `USER_ID`, `USER_NAME`, `QUESTION_TITLE`, `QUESTION_FILE_PATH`, `QUESTION_FILE_NAME`, `QUESTION_SUBMIT_DATE`) "
      #   +"VALUES(\"{0}\",\"{1}\",{2},\"{3}\",\"{4}\",\"{5}\",\"{6}\",\"{7}\",DATE()".format(qid,category3_id,type_name,
      #     self.current_user["uid"],self.current_user["uname"],title,path,file_name))
      self.redirect("/problems/manage/new")
    elif oper=="update":
      qid = self.get_argument("qid")
      if self.current_user["privilege"] in [3]:
        uid = self.current_user["uid"]
      else:
        uid = "USER_ID"
      title = self.get_argument("inputName").encode("UTF-8")
      path=os.path.join(os.path.dirname(__file__),'static/questions')
      file_name = qid+".pdf"
      if len(self.request.files)>0:
        file_metas=self.request.files['file']
        for meta in file_metas:
          with open(os.path.join(path,file_name),"wb") as up:
            up.write(meta["body"])
      sql = "UPDATE QUESTION SET QUESTION_TITLE=\"{0}\" WHERE QUESTION_ID=\"{1}\" AND USER_ID={2}".format(title,qid,uid)
      print(sql)
      self.db.execute(sql)
      self.redirect("/problems/manage/")




class QuestionQueryHandler(BaseHandler):

  def get(self):
    m_category1 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 1")
    m_category2 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 2")
    m_category3 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 3")
    authors = self.db.query("SELECT DISTINCT USER_ID, USER_NAME FROM QUESTION")
    self.render("result_query.html", user=self.current_user, authors=authors, m_category1=m_category1, m_category2=m_category2, m_category3=m_category3)

  def post(self):
    query_category1 = self.get_argument("category1",default="all",strip=True)
    query_category2 = self.get_argument("category2",default="all",strip=True)
    query_category3 = self.get_argument("category3",default="all",strip=True)
    author = self.get_argument("author",default="all",strip=True)
    stime = self.get_argument("stime",default="0",strip=True)
    etime = self.get_argument("etime",default="0",strip=True)
    start = int(self.get_argument("start",default=0))
    length = int(self.get_argument("length",default=10))
    category_id_list = []

    if query_category1 == "all":
      m_category1 = self.db.query("SELECT QUESTION_TYPE_ID FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 1")
    else:
      m_category1 = [{"QUESTION_TYPE_ID":query_category1}]

    if query_category2 == "all":
      m_category1_str = ""
      for m_cat in m_category1:
        m_category1_str = m_category1_str + "\'" + m_cat["QUESTION_TYPE_ID"] + "\',"
      m_category1_str = m_category1_str + "\'\'"
      sql = "SELECT QUESTION_TYPE_ID FROM QUESTION_TYPE WHERE BELONG_QUESTION_TYPE_ID IN (" + m_category1_str + ")"
      print(sql)
      m_category2 = self.db.query(sql)
    else:
      m_category2 = [{"QUESTION_TYPE_ID":query_category2}]
      print(m_category2)

    if query_category3 == "all":
      m_category2_str = ""
      for m_cat in m_category2:
        m_category2_str = m_category2_str + "\'" + m_cat["QUESTION_TYPE_ID"] + "\',"
      m_category2_str = m_category2_str + "\'\'"
      m_category3 = self.db.query("SELECT QUESTION_TYPE_ID FROM QUESTION_TYPE WHERE BELONG_QUESTION_TYPE_ID IN (" + m_category2_str + ")")
      category_id_list = m_category1 + m_category2 + m_category3
    else:
      m_category3 = [{"QUESTION_TYPE_ID":query_category3}]
      category_id_list = m_category3

    category_id_list_str = ""
    for m_cat in category_id_list:
      category_id_list_str = category_id_list_str + "\'" + m_cat["QUESTION_TYPE_ID"] + "\',"
    category_id_list_str = category_id_list_str + "\'\'"
    if author == "all":
      sql_condition = "WHERE QUESTION_TYPE_ID IN (" + category_id_list_str + ")"
      #sql = "SELECT QUESTION_ID, QUESTION_TYPE_ID, USER_ID, USER_NAME, QUESTION_TITLE FROM QUESTION WHERE QUESTION_TYPE_ID IN (" + category_id_list_str + ")"
    else:
      sql_condition = "WHERE USER_ID={0} AND QUESTION_TYPE_ID IN (".format(author) + category_id_list_str + ")"
      #sql = "SELECT QUESTION_ID, QUESTION_TYPE_ID, USER_ID, USER_NAME, QUESTION_TITLE FROM QUESTION WHERE USER_ID={0} AND QUESTION_TYPE_ID IN (".format(author) + category_id_list_str + ")"
    if len(stime)==8 and len(etime)==8 :
        stime = datetime.date(int(stime[0:4]),int(stime[4:6]),int(stime[6:8]))
        etime = datetime.date(int(etime[0:4]),int(etime[4:6]),int(etime[6:8]))
        sql_condition = sql_condition + " AND QUESTION_SUBMIT_DATE >=\'{0}\' AND  QUESTION_SUBMIT_DATE <=\'{1}\'".format(stime.strftime("%Y-%m-%d"),etime.strftime("%Y-%m-%d"))
    
    result_length = self.db.get("SELECT COUNT(QUESTION_ID) FROM QUESTION " + sql_condition)["COUNT(QUESTION_ID)"]
    sql = "SELECT QUESTION_ID, QUESTION_TYPE_ID, USER_ID, USER_NAME, QUESTION_TITLE FROM QUESTION " + sql_condition + "LIMIT {0}, {1}".format(start,length)

    print(sql)
    result = self.db.query(sql)
    self.write(json.dumps({"code":0,"result":result,"length":result_length}))

class GenerateHandler(BaseHandler):

  def get(self):
    if self.current_user["privilege"] < 2:
      self.redirect("/login")
    self.render("account_generate.html",user=self.current_user)

  def post(self):
    if self.current_user["privilege"] > 1:
      strHead = self.get_argument("strHead",default="")
      strEnd = self.get_argument("strEnd",default="")
      start = int(self.get_argument("start",default="0"))
      size = int(self.get_argument("size",default="0"))
      account_type = int(self.get_argument("account_type",default="1"))

      for i in range(start, start+size):
        uname = strHead + str(i) + strEnd
        self.db.execute("INSERT INTO USER (USER_NAME,USER_TYPE) VALUES (\"{0}\",{1})".format(uname,account_type))
      result = self.db.query("SELECT USER_TYPE,USER_NAME FROM USER WHERE USER_NAME LIKE \""+strHead+'%%'+strEnd+"\"")
      self.write(json.dumps({"code":0,"result":result}))

class JudgeHandler(BaseHandler):
  
  def get(self):
    ratelist = []
    fdir = os.path.join(os.path.dirname(__file__),'static/code_files/')
    qid = self.get_argument("qid",default="")
    rid_list = self.get_argument("rid",default="").split("_")
    if qid and len(rid_list)==4:
      #查看统计信息
      cppfilelist = glob.glob(fdir+qid+"/"+'*.cpp') + glob.glob(fdir+qid+"/"+'*.c')
      ratelist=[]
      print(cppfilelist)
      filenamelist=[]
      for cpp in cppfilelist:
        filenamelist.append(cpp.split("/")[-1])
      num=int(rid_list[1])
      lefts=int(rid_list[2])
      rights=int(rid_list[3])
      ret = os.fork()
      if ret == 0:
          os.execl("stat","stat",cppfilelist[lefts],cppfilelist[rights])
      else:
          os.wait()

      ret = os.fork()
      if ret == 0:
          os.execl("cppgst","cppgst",cppfilelist[lefts],cppfilelist[rights],str(lefts),str(rights),"15")
      else:
          os.wait()

      fstat = open("./doc/sim.stat","r")
      strlist = fstat.readlines()
      fstat.close()

      fvalue = open("./doc/simvalue.stat","r")
      rate2 = fvalue.readline()
      rate2 = rate2.rstrip('\n')
      rate2 = string.atof(rate2)
      fvalue.close()

      fgst = open("./static/detection_result/"+qid+"/sim.gst","r")
      tmplist = fgst.readlines()
      fgst.close()

      for i in range(0,len(tmplist)):
          tmplist[i]=tmplist[i].rstrip('\n')
          ratelist.append(0)
          (tmp1,tmp2,ratelist[i])=tmplist[i].split("\t")
          ratelist[i] = string.atof(ratelist[i])

      statlistl = []
      statlistr = []
      for i in range(0,len(strlist)):
          strlist[i] = strlist[i].rstrip('\n')
          statlistl.append(0)
          statlistr.append(0)
          (statlistl[i],statlistr[i]) = strlist[i].split("\t")
          statlistl[i] = string.atof(statlistl[i])
          statlistr[i] = string.atof(statlistr[i])
      self.render('detail.html',user=self.current_user,num=num,left=lefts,right=rights,filelist=filenamelist,sl=statlistl,sr=statlistr,rate=ratelist[num],rate2=rate2,qid=qid)

    elif qid:
      
      leftlist = []
      rightlist = []
      filenamelist=[]
      cppfilelist = glob.glob(fdir+qid+"/"+'*.cpp') + glob.glob(fdir+qid+"/"+'*.c')
      print(cppfilelist)
      for cpp in cppfilelist:
        filenamelist.append(cpp.split("/")[-1])
      print(filenamelist)
      if not os.path.isfile("./static/detection_result/"+qid+"/sim.gst"):
        self.render("judge_error.html",user=self.current_user)
        return
      fgst = open("./static/detection_result/"+qid+"/sim.gst","r")
      strlist = fgst.readlines()
      fgst.close()

      for i in range(0,len(strlist)):
          strlist[i]=strlist[i].rstrip('\n')
          leftlist.append(0)
          rightlist.append(0)
          ratelist.append(0)
          (leftlist[i],rightlist[i],ratelist[i])=strlist[i].split("\t")
          leftlist[i] = string.atoi(leftlist[i])
          rightlist[i] = string.atoi(rightlist[i])
          ratelist[i] = string.atof(ratelist[i])

      self.render('judge_result.html',qid=qid,filelist=filenamelist,leftlist=leftlist,rightlist=rightlist,ratelist=ratelist,user=self.current_user)    
    else:
      m_category1 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 1")
      m_category2 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 2")
      m_category3 = self.db.query("SELECT * FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 3")
      authors = self.db.query("SELECT DISTINCT USER_ID, USER_NAME FROM QUESTION")      
      self.render("judge.html",user=self.current_user,m_category1=m_category1,authors=authors, m_category2=m_category2, m_category3=m_category3)

  def post(self):
    query_category1 = self.get_argument("category1",default="all",strip=True)
    query_category2 = self.get_argument("category2",default="all",strip=True)
    query_category3 = self.get_argument("category3",default="all",strip=True)
    author = self.get_argument("author",default="all",strip=True)
    stime = self.get_argument("stime",default="0",strip=True)
    etime = self.get_argument("etime",default="0",strip=True)
    start = int(self.get_argument("start",default=0))
    length = int(self.get_argument("length",default=10))
    category_id_list = []

    if query_category1 == "all":
      m_category1 = self.db.query("SELECT QUESTION_TYPE_ID FROM QUESTION_TYPE WHERE QUESTION_TYPE_LEVEL = 1")
    else:
      m_category1 = [{"QUESTION_TYPE_ID":query_category1}]

    if query_category2 == "all":
      m_category1_str = ""
      for m_cat in m_category1:
        m_category1_str = m_category1_str + "\'" + m_cat["QUESTION_TYPE_ID"] + "\',"
      m_category1_str = m_category1_str + "\'\'"
      sql = "SELECT QUESTION_TYPE_ID FROM QUESTION_TYPE WHERE BELONG_QUESTION_TYPE_ID IN (" + m_category1_str + ")"
      print(sql)
      m_category2 = self.db.query(sql)
    else:
      m_category2 = [{"QUESTION_TYPE_ID":query_category2}]
      print(m_category2)

    if query_category3 == "all":
      m_category2_str = ""
      for m_cat in m_category2:
        m_category2_str = m_category2_str + "\'" + m_cat["QUESTION_TYPE_ID"] + "\',"
      m_category2_str = m_category2_str + "\'\'"
      m_category3 = self.db.query("SELECT QUESTION_TYPE_ID FROM QUESTION_TYPE WHERE BELONG_QUESTION_TYPE_ID IN (" + m_category2_str + ")")
      category_id_list = m_category1 + m_category2 + m_category3
    else:
      m_category3 = [{"QUESTION_TYPE_ID":query_category3}]
      category_id_list = m_category3

    category_id_list_str = ""
    for m_cat in category_id_list:
      category_id_list_str = category_id_list_str + "\'" + m_cat["QUESTION_TYPE_ID"] + "\',"
    category_id_list_str = category_id_list_str + "\'\'"
    if author == "all":
      sql_condition = "WHERE QUESTION_TYPE_ID IN (" + category_id_list_str + ")"
      #sql = "SELECT QUESTION_ID, QUESTION_TYPE_ID, USER_ID, USER_NAME, QUESTION_TITLE FROM QUESTION WHERE QUESTION_TYPE_ID IN (" + category_id_list_str + ")"
    else:
      sql_condition = "WHERE USER_ID={0} AND QUESTION_TYPE_ID IN (".format(author) + category_id_list_str + ")"
      #sql = "SELECT QUESTION_ID, QUESTION_TYPE_ID, USER_ID, USER_NAME, QUESTION_TITLE FROM QUESTION WHERE USER_ID={0} AND QUESTION_TYPE_ID IN (".format(author) + category_id_list_str + ")"
    if len(stime)==8 and len(etime)==8 :
        stime = datetime.date(int(stime[0:4]),int(stime[4:6]),int(stime[6:8]))
        etime = datetime.date(int(etime[0:4]),int(etime[4:6]),int(etime[6:8]))
        sql_condition = sql_condition + " AND QUESTION_SUBMIT_DATE >=\'{0}\' AND  QUESTION_SUBMIT_DATE <=\'{1}\'".format(stime.strftime("%Y-%m-%d"),etime.strftime("%Y-%m-%d"))
    
    result_length = self.db.get("SELECT COUNT(QUESTION_ID) FROM QUESTION " + sql_condition)["COUNT(QUESTION_ID)"]
    sql = "SELECT QUESTION_ID, QUESTION_TYPE_ID, USER_ID, USER_NAME, QUESTION_TITLE FROM QUESTION " + sql_condition + "LIMIT {0}, {1}".format(start,length)

    print(sql)
    result = self.db.query(sql)
    self.write(json.dumps({"code":0,"result":result,"length":result_length}))


class ExamHandler(BaseHandler):
    def get(self):

        global fdir
        global cppfilelist
        qid = self.get_argument("qid",default="")
        if not qid:
          self.redirect("/problems/choose")
        #fdir = "./sour/"
        fdir = os.path.join(os.path.dirname(__file__),'static/code_files/'+qid)
        if not os.path.exists(fdir):
          os.mkdir(fdir)
        #os.system("rm -rf "+fdir)
        #os.mkdir(fdir)
        cppfilelist = []
        self.render('default.html',filelist=[],size=0,err=0,qid=qid,user=self.current_user)


class UpLoadHandler(BaseHandler):
    def post(self):
        global fdir
        global cppfilelist
        global filenamelist
        if fdir[-1]!='/':
          fdir = fdir+'/'
        print(fdir)
        qid = self.get_argument("qid",default="")
        if not qid:
          self.redirect("/problems/query")
        print(qid)
        # if not os.path.exists(os.path.join(os.path.dirname(__file__),'static/code_files/'+qid)):
        #     os.mkdir(os.path.join(os.path.dirname(__file__),'static/code_files/'+qid))
        #     q_path = os.path.join(os.path.dirname(__file__),'static/code_files/'+qid)
        try:
            file_dict_list = self.request.files['file']
            for file_dict in file_dict_list:
                filename = file_dict["filename"]
                if filename[-4:]==".cpp" or filename[-2:]==".c":
                    cppfilelist.append(fdir+filename)
                    tempf = open(fdir+filename,"wb")
                    tempf.write(file_dict["body"])
                    #tempf1 = open(q_path+"/"+filename,"wb")
                    #tempf1.write(file_dict["body"])
                    tempf.close()
                    #tempf1.close()
            cppfilelist = glob.glob(fdir+'*.cpp')+glob.glob(fdir+'*.c')
            cppfilelist.sort()
            filenamelist = []
            for i in range(0,len(cppfilelist)):
                filenamelist.append(0)
                tmp = cppfilelist[i].split('/')[-1]
                filenamelist[i]=tmp
                sql ="INSERT INTO `CODE_FILE`(`USER_ID`, `QUESTION_ID`, `FILE_PATH`, `FILE_NAME`, `SUBMIT_DATE`) VALUES ({0},\"{1}\",\"{2}\",\"{3}\",NOW())".format(self.current_user["uid"],qid,fdir,tmp)
                self.db.execute(sql)
            self.render('default.html',filelist=filenamelist,size=len(cppfilelist),err=0,qid=qid,user=self.current_user)
        except:
            self.render('default.html',filelist=[],size=0,err=-5,user=self.current_user)

class OnLoadHandler(BaseHandler):
    def post(self):
        global fdir
        global cppfilelist
        global tmpfilelist
        fdir = self.get_argument('path')
        if fdir[-1]!='/':
            fdir = fdir+'/'
        
        if not os.path.exists(fdir):
            self.render('default.html',filelist=[],size=0,err=-1,user=self.current_user)
            return
        if os.path.isfile(fdir):
            self.render('default.html',filelist=[],size=0,err=-2,user=self.current_user)
            return
        cppfilelist = glob.glob(fdir+'*.cpp') + glob.glob(fdir+'*.c')
        cppfilelist.sort()

        if len(cppfilelist) < 2 :
            self.render('default.html',filelist=[],size=0,err=-3,user=self.current_user)
            return

        self.render('default.html',filelist=cppfilelist,size=len(cppfilelist),err=0,user=self.current_user)

class CheckHandler(BaseHandler):
    def post(self):
        global fdir
        global cppfilelist
        global filenamelist
        global tmpfilelist
        global timelists
        global i
        global j

        if len(cppfilelist) < 2 :
            self.render('default.html',filelist=[],size=0,err=-4)
            return
        qid = self.get_argument("qid")
        sim.PreProc(fdir)
        tmpfilelist = glob.glob(fdir+'*.tmp')
        tmpfilelist.sort()
        fgst = open("./doc/sim.gst","w")
        fgst.close()
        
        timelists = []
        for i in range(0,len(tmpfilelist)+1):
            for j in range(0,len(tmpfilelist)+1):
                timelists.append(0)
        i = 0
        j = 0
        self.render('check.html',x=0,y=0,filelist=filenamelist,timelist=timelists,size=len(tmpfilelist),num=1,user=self.current_user)
        #for i in range(0,len(tmpfilelist)):
        #   for j in range(i+1,len(tmpfilelist)):
        #       #print tmpfilelist[i],"===",tmpfilelist[j]
        #       exebegin = time.time()
        #       ret = os.fork()
        #       if ret == 0:
        #           os.execl("gst","gst",tmpfilelist[i],tmpfilelist[j],str(i),str(j),"30")
        #       else:
        #           os.wait()
        #       exeend = time.time()
        #       timelists[i*len(tmpfilelist)+j]=exeend-exebegin
        #self.render('check.html',x=i,y=j,filelist=cppfilelist,timelist=timelists,size=len(tmpfilelist))

class PollHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        if self.request.connection.stream.closed():
            return
        global fdir
        global cppfilelist
        global filenamelist
        global tmpfilelist
        global timelists
        global i
        global j
        j=j+1
        if(j>=len(tmpfilelist)):
            i=i+1
            j=i+1
        if(i>=len(tmpfilelist)-1 and j>=len(tmpfilelist)):
            return

        exebegin = time.time()
        ret = os.fork()
        if ret == 0:
            os.execl("gst","gst",tmpfilelist[i],tmpfilelist[j],str(i),str(j),"30")
        else:
            os.wait()
        exeend = time.time()
        timelists[i*len(tmpfilelist)+j] = exeend-exebegin

        datadict={}
        datadict["cppfilelist"]=filenamelist
        datadict["timelists"]=timelists
        datadict["i"]=i
        datadict["j"]=j
        datadict["length"]=len(cppfilelist)
        #num = random.randint(1, 100)
        tornado.ioloop.IOLoop.instance().add_timeout(
            time.time(),
            lambda: self.send(data=datadict, callback=self.get)
        )
        qid = fdir.split("/")[-2]
        fdir2 = os.path.join(os.path.dirname(__file__),'static/detection_result/'+qid)
        if not os.path.exists(fdir2):
          os.mkdir(fdir2)
        shutil.copy("./doc/sim.gst",fdir2+"/sim.gst")     
    def send(self, data, callback):
        try:
            data = json.dumps(data)
            self.write(str(data))
            self.finish()
        except:
            pass

class ResultHandler(BaseHandler):
    def get(self):
        global fdir
        global cppfilelist
        global filenamelist
        global tmpfilelist
        global timelists
        
        global ratelist
        global leftlist
        global rightlist
        ratelist = []
        leftlist = []
        rightlist = []
        fgst = open("./doc/sim.gst","r")
        strlist = fgst.readlines()
        fgst.close()

        for i in range(0,len(strlist)):
            strlist[i]=strlist[i].rstrip('\n')
            leftlist.append(0)
            rightlist.append(0)
            ratelist.append(0)
            (leftlist[i],rightlist[i],ratelist[i])=strlist[i].split("\t")
            leftlist[i] = string.atoi(leftlist[i])
            rightlist[i] = string.atoi(rightlist[i])
            ratelist[i] = string.atof(ratelist[i])

        self.render('result.html',filelist=filenamelist,leftlist=leftlist,rightlist=rightlist,ratelist=ratelist,user=self.current_user)

class ReportHandler(BaseHandler):
    def get(self):
        def findset(x):
            global father
            if father[x]==x:
                return x
            else:
                father[x]=findset(father[x])
                return father[x]
        def unionset(x,y):
            global father
            fx=findset(x)
            fy=findset(y)
            if fx!=fy:
                father[x]=findset(y)

        global fdir
        global cppfilelist
        global tmpfilelist
        global timelists
        
        global ratelist
        global leftlist
        global rightlist
        global father

        rcdCopy=0
        rcdSusp=0
        rcdSafe=0
        for rate in ratelist:
            if rate>0.9-0.00000001:
                rcdCopy+=1
            elif rate>0.8-0.00000001:
                rcdSusp+=1
            else:
                rcdSafe+=1
        rcdCopy = (rcdCopy*1.0/len(ratelist))*100
        rcdSusp = (rcdSusp*1.0/len(ratelist))*100
        rcdSafe = (rcdSafe*1.0/len(ratelist))*100
        rcdPerc=[0,0,0,0,0,0,0,0,0,0]
        for rate in ratelist:
            if rate>0.9-0.00000001:
                rcdPerc[9]+=1
            elif rate>0.8-0.00000001:
                rcdPerc[8]+=1
            elif rate>0.7-0.00000001:
                rcdPerc[7]+=1
            elif rate>0.6-0.00000001:
                rcdPerc[6]+=1
            elif rate>0.5-0.00000001:
                rcdPerc[5]+=1
            elif rate>0.4-0.00000001:
                rcdPerc[4]+=1
            elif rate>0.3-0.00000001:
                rcdPerc[3]+=1
            elif rate>0.2-0.00000001:
                rcdPerc[2]+=1
            elif rate>0.1-0.00000001:
                rcdPerc[1]+=1
            else:
                rcdPerc[0]+=1
        fileprop=[]
        for file in cppfilelist:
            fileprop.append(0)
        for i in range(0,len(ratelist)):
            if ratelist[i]>0.8-0.00000001:
                fileprop[leftlist[i]]=1
                fileprop[rightlist[i]]=1
        for i in range(0,len(ratelist)):
            if ratelist[i]>0.9-0.00000001:
                fileprop[leftlist[i]]=2
                fileprop[rightlist[i]]=2
        fileCopy=0
        fileSusp=0
        fileSafe=0
        for prop in fileprop:
            if prop==2:
                fileCopy+=1
            elif prop==1:
                fileSusp+=1
            else:
                fileSafe+=1
        fileCopy=(fileCopy*1.0/len(fileprop))*100
        fileSusp=(fileSusp*1.0/len(fileprop))*100
        fileSafe=(fileSafe*1.0/len(fileprop))*100
        
        filenamelist = []
        for i in range(0,len(cppfilelist)):
            filenamelist.append(0)
            filenamelist[i]=cppfilelist[i].split('/')[-1]
        filedict = []
        for i in range(0,len(filenamelist)):
            filedict.append([])
            for j in range(0,len(filenamelist)):
                filedict[i].append(1)
        
        for i in range(0,len(ratelist)):
            filedict[leftlist[i]][rightlist[i]]=ratelist[i]
            filedict[rightlist[i]][leftlist[i]]=ratelist[i]

        father=[]
        for i in range(0,len(filenamelist)):
            father.append(i)
        for i in range(0,len(ratelist)):
            if ratelist[i]>0.9-0.00000001:
                fl = findset(leftlist[i])
                fr = findset(rightlist[i])
                unionset(fl,fr)

        sets=[]
        prt =[]
        for i in range(0,len(filenamelist)):
            sets.append(findset(i))
            prt.append(0)

        setdict={}
        k = 0
        for i in range(0,len(filenamelist)):
            if prt[i]==0:
                prt[i]=1
                addlist=[]
                addlist.append(filenamelist[i])
                for j in range(i+1,len(filenamelist)):
                    if sets[j]==sets[i] and prt[j]==0:
                        prt[j]=1
                        addlist.append(filenamelist[j])
                k=k+1
                setdict[k]=addlist

        self.render('report.html',rcdCopy=rcdCopy,rcdSusp=rcdSusp,rcdSafe=rcdSafe,
        rcdPerc=rcdPerc,
        fileCopy=fileCopy,fileSusp=fileSusp,fileSafe=fileSafe,
        filenamelist=filenamelist,filedict=filedict,
        setdict=setdict,user=self.current_user)

class DetailHandler(BaseHandler):
    def get(self,num,left,right):
        global cppfilelist
        global filenamelist
        global ratelist
        num=string.atoi(num)
        lefts=string.atoi(left)
        rights=string.atoi(right)
        ret = os.fork()
        if ret == 0:
            os.execl("stat","stat",cppfilelist[lefts],cppfilelist[rights])
        else:
            os.wait()

        ret = os.fork()
        if ret == 0:
            os.execl("cppgst","cppgst",cppfilelist[lefts],cppfilelist[rights],str(lefts),str(rights),"15")
        else:
            os.wait()

        fstat = open("./doc/sim.stat","r")
        strlist = fstat.readlines()
        fstat.close()

        fvalue = open("./doc/simvalue.stat","r")
        rate2 = fvalue.readline()
        rate2 = rate2.rstrip('\n')
        rate2 = string.atof(rate2)
        fvalue.close()

        statlistl = []
        statlistr = []
        for i in range(0,len(strlist)):
            strlist[i] = strlist[i].rstrip('\n')
            statlistl.append(0)
            statlistr.append(0)
            (statlistl[i],statlistr[i]) = strlist[i].split("\t")
            statlistl[i] = string.atof(statlistl[i])
            statlistr[i] = string.atof(statlistr[i])
        self.render('detail.html',user=self.current_user,num=num,left=lefts,right=rights,filelist=filenamelist,sl=statlistl,sr=statlistr,rate=ratelist[num],rate2=rate2)

class MarkHandler(BaseHandler):
    def get(self,num,left,right,cas):
        global cppfilelist
        num=string.atoi(num)
        lefts=string.atoi(left)
        rights=string.atoi(right)
        cas=string.atoi(cas)
        qid = self.get_argument("qid",default="")
        print("$"+qid)
        if not ('cppfilelist' in dir()) and qid:
          fdir = os.path.join(os.path.dirname(__file__),'static/code_files/')
          cppfilelist = glob.glob(fdir+qid+"/"+'*.cpp') + glob.glob(fdir+qid+"/"+'*.c')

        colorlist = ['#1ABC9C','#2ECC71','#3498DB','#9B59B6',
        '#F1C40F','#E67E22','#E74C3C','#16A085','#27AE60',
        '#2980B9','#8E44AD','#F39C12','#D35400','#C0392B']
        colornum = len(colorlist)

        mllist = []
        mrlist = []
        lenlist = []

        matchfile = open("./doc/"+left+"_"+right+".match","r")
        matchlist = matchfile.readlines()
        matchfile.close()
        for i in range(0,len(matchlist)):
            matchlist[i]=matchlist[i].rstrip("\n")
            mllist.append(0)
            mrlist.append(0)
            lenlist.append(0)
            (mllist[i],mrlist[i],lenlist[i])=matchlist[i].split("\t")
            mllist[i] = string.atoi(mllist[i])
            mrlist[i] = string.atoi(mrlist[i])
            lenlist[i] = string.atoi(lenlist[i])

        leftcpp = open(cppfilelist[lefts],"r")
        leftstr = leftcpp.read()
        leftcpp.close()
        leftmark = []
        for i in leftstr:
            leftmark.append(-1)



        rightcpp = open(cppfilelist[rights],"r")
        rightstr = rightcpp.read()
        rightcpp.close()
        rightmark = []
        for i in rightstr:
            rightmark.append(-1)

        for i in range(0,len(lenlist)):
            for j in range(0,lenlist[i]):
                leftmark[mllist[i]+j]=i%colornum
                rightmark[mrlist[i]+j]=i%colornum
        #print leftstr
        
        if cas == 1 :
            self.render('mark.html',sstr=leftstr,smark=leftmark,clist=colorlist,cnum=colornum)
            return
        if cas == 2 :
            self.render('mark.html',sstr=rightstr,smark=rightmark,clist=colorlist,cnum=colornum)
            return

if __name__ == '__main__':
    tornado.options.parse_command_line()
    http_server = tornado.httpserver.HTTPServer(Application())
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
