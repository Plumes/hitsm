#!/usr/bin/python
#-*- coding:utf-8 -*-

import sys
import os
import glob
import re
import ctypes
import pdb
import datetime
import time

keyWordDict = {
'asm':'ASM',
'auto':'AUTO',
'bool':'BOOL',
'break':'BREAK',
'case':'CASE',
'catch':'CATCH',
'char':'CHAR',
'class':'CLASS',
'const':'CONST',
'continue':'CONTINUE',
'default':'DEFAULT',
'delete':'DELETE',
'do':'DO',
'double':'FLOAT',#same as float
'else':'ELSE',
'enum':'ENUM',
'explicit':'EXPLICIT',
'export':'EXPORT',
'extern':'EXTERN',
'false':'FALSE',
'float':'FLOAT',
'for':'FOR',
'friend':'FRIEND',
'goto':'GOTO',
'if':'IF',
'inline':'INLINE',
'int':'INT',
'long long':'INT',#same as int
#'long long':'INT',#same as int
'mutable':'MUTABLE',
'namespace':'NAMESPACE',
'new':'NEW',
'operator':'OPERATOR',
'private':'PRIVATE',
'protected':'PROTECTED',
'public':'PUBLIC',
'register':'REGISTER',
'return':'RETURN',
'short':'INT',#same as int
'signed':'',#ignored
'sizeof':'SIZEOF',
'static':'STATIC',
'struct':'STRUCT',
'switch':'SWITCH',
'template':'TEMPLATE',
'this':'THIS',
'throw':'THROW',
'true':'TRUE',
'try':'TRY',
'typedef':'TYPEDEF',
'typeid':'TYPEID',
'typename':'TYPENAME',
'union':'UNION',
'unsigned':'UNSIGNED',
'using':'USING',
'virtual':'VIRTUAL',
'void':'VOID',
'volatile':'VOLATILE',
'while':'WHILE'
}
keyFuncDict = {
'gets':'INPUT_DECL',
'getc':'INPUT_DECL',
'getch':'INPUT_DECL',
'getche':'INPUT_DECL',
'getchar':'INPUT_DECL',
'scanf':'INPUT_DECL',
'getline':'INPUT_DECL',
'puts':'OUTPUT_DECL',
'putc':'OUTPUT_DECL',
'putch':'OUTPUT_DECL',
'putche':'OUTPUT_DECL',
'putchar':'OUTPUT_DECL',
'printf':'OUTPUT_DECL',
'fgets':'FILE_IN',
'fgetc':'FILE_IN',
'fscanf':'FILE_IN',
'fread':'FILE_IN',
'fputs':'FILE_OUT',
'fputc':'FILE_OUT',
'fprintf':'FILE_OUT',
'fwrite':'FILE_OUT',
'main':'MAIN_FUNC',
'open':'FILE_OPEN',
'close':'FILE_CLOSE'
}
ioStreamDict = {
'cin':'INPUT_DECL',
'cout':'OUTPUT_DECL',
'cerr':'OUTPUT_DECL'
}
opChaDict = {
'<<=':'OP01',
'>>=':'OP02',
'::':'OP03',
'+=':'OP04',
'-=':'OP05',
'*=':'OP06',
'/=':'OP07',
'&=':'OP08',
'%=':'OP09',
'^=':'OP10',
'&&':'OP11',
'||':'OP12',
'->':'OP13',
'++':'OP14',
'--':'OP15',
'<<':'OP16',
'>>':'OP17',
'==':'OP18',
'.':'OP19',
'~':'OP20',
'!':'OP21',
'-':'OP22',
'+':'OP23',
'*':'OP24',
'&':'OP25',
'/':'OP26',
'%':'OP27',
'^':'OP28',
'|':'OP39',
'=':'OP30',
'{':'LB',
'}':'RB',
'(':'LS',
')':'RS',
'[':'LM',
']':'RM',
'<':'LL',
'>':'RL'
}
opPatList = [
'<<=',
'>>=',
'::',
'\+=',
'-=',
'\*=',
'/=',
'&=',
'%=',
'\^=',
'&&',
'\|\|',
'->',
'\+\+',
'--',
'<<',
'>>',
'==',
'\.',
'~',
'!',
'-',
'\+',
'\*',
'&',
'/',
'%',
'\^',
'\|',
'=',
'\{',
'\}',
'\(',
'\)',
'\[',
'\]',
'<',
'>'
]
def keyWordPat(matched):
	stra = matched.group("a")
	strb = matched.group("b")
	strc = matched.group("c")
	rtnStr = stra + ' ' + keyWordDict[strb] + ' ' + strc
	return rtnStr
def keyFuncPat(matched):
	stra = matched.group("a")
	strb = matched.group("b")
	strc = matched.group("c")
	rtnStr = stra + ' ' + keyFuncDict[strb] + ' '
	return rtnStr
def ioStreamPat(matched):
	stra = matched.group("a")
	strb = matched.group("b")
	strc = matched.group("c")
	rtnStr = stra + ' ' + ioStreamDict[strb] + strc
	return rtnStr
def opChaPat(matched):
	stra = matched.group("a")
	rtnStr = ' ' + opChaDict[stra] + ' '
	return rtnStr
def order(a,b):
	if a==b:
		return 0
	elif len(a)>len(b):
		return -1
	elif len(a)==len(b) and a>b:
		return -1
	else:
		return 1

#GstLib = ctypes.cdll.LoadLibrary("./gstso.so")

def PreProc(fdir):

	global keyWordDict
	global keyFuncDict
	global ioStreamDict
	global opChaDict
	global opPatList

	cppfilelist = glob.glob(fdir+'*.cpp') + glob.glob(fdir+'*.c')
	cppfilelist.sort()
	#for i in cppfilelist:
	#	print i
	#print len(cppfilelist)
	#sys.exit()
	
	if len(cppfilelist) < 2:
		print 'The cpp files is too few to be compared with!'
		sys.exit()
	
	for cppfile in cppfilelist:
		fi = open(cppfile,'r')
		fo = open(cppfile+'.tmp','w');
		s = fi.read()
		#print cppfile
		#print "*"*40
		#print s
		t = len(s)
		#print '*'*40
	
		s = s.lower()
		s = re.sub('"(.|\n)+?"',"CONST_STR",s)
		s = re.sub("('.')|('\\\w')","CONST_CHAR",s)
		s = re.sub("/\*(.|\n)*?\*/"," ",s)
		s = re.sub("//.*\n"," \n",s)
		s = re.sub("#.+?\n"," ",s)
		s = re.sub("using namespace.+?\n","",s)
	
		s = re.sub(" \*(\W)"," P \g<1>",s)
		s = re.sub(" \*([a-z_])"," P \g<1>",s)
	
		typedefList = re.findall("typedef.+?;",s)
		for each in typedefList:
			each = each.rstrip(';')
			word = each.split(" ")
			typeDef = " "
			typeDef = typeDef.join(word[1:-1])
			typeDef = " \g<1>" + typeDef + "\g<3> "
			pattern = "(\W)(" + word[-1] + ")(\W)"
			s = re.sub(pattern,typeDef,s)
		s = re.sub("typedef.+?;"," ",s)
		#deal with typedef
	
		for each in keyWordDict.keys():
			pattern = '(?P<a>(\W))(?P<b>(' + each + '))(?P<c>(\W))'
			s = re.sub(pattern,keyWordPat,s)
		for each in keyWordDict.keys():#repeat
			pattern = '(?P<a>(\W))(?P<b>(' + each + '))(?P<c>(\W))'
			s = re.sub(pattern,keyWordPat,s)
		for each in keyFuncDict.keys():
			pattern = '(?P<a>(\W))(?P<b>(' + each + '))(?P<c>(\(.*?\)))'
			s = re.sub(pattern,keyFuncPat,s)
		for each in ioStreamDict.keys():
			pattern = '(?P<a>(\W))(?P<b>(' + each + '))(\W)(.*?)(?P<c>(;))'
			s = re.sub(pattern,ioStreamPat,s)
		
		opPatList = sorted(opPatList,cmp = lambda a,b:order(a,b))
		for each in opPatList:
			pattern = '(?P<a>(' + each + '))'
			s = re.sub(pattern,opChaPat,s)
	
		pattern = "(\W)([_a-z]\w*?)(\W)"
		s = re.sub(pattern,"\g<1> VAR_ID \g<3>",s)
		s = re.sub(pattern,"\g<1> VAR_ID \g<3>",s)#repeat
	
		pattern = "(\W)([_a-z]\w*?)(\(.*?\))(\W)"
		s = re.sub(pattern,"\g<1> FUNC_ID \g<4>",s)
		s = re.sub(pattern,"\g<1> FUNC_ID \g<4>",s)#repeat
	
		s = re.sub(",|;"," ",s)
		s = re.sub("( |\r|\t|\v|\f)+"," ",s)
		s = re.sub("\n ","\n",s)
		s = re.sub(" \n","\n",s)
		s = re.sub("\n\n","\n",s)
		s = s.strip("\n")
		s = s.strip(" ")
		s = s.upper()
	
		fo.write(s)
		fi.close()
		fo.close()
		#print s
		#print "*"*40
		#print t,' ',len(s)
		#print cppfile
		#something = raw_input("input something")
	
	#os.execl("/home/youg/HITSim/gst","/home/youg/HITSim/gst","/home/youg/HITSim/sample/raw.cpp.tmp","/home/youg/HITSim/sample/raw1.cpp.tmp")
	
def MainProc(fdir):
	
	global keyWordDict
	global keyFuncDict
	global ioStreamDict
	global opChaDict
	global opPatList
	
	tmpfilelist = glob.glob(fdir+'*.tmp')
	tmpfilelist.sort()
	
	for i in tmpfilelist:
		print i
	print len(tmpfilelist)
	
	fgst = open("./doc/sim.gst","w")
	fgst.close()
	
	for i in range(0,len(tmpfilelist)):
		for j in range(i+1,len(tmpfilelist)):
			#print tmpfilelist[i],"===",tmpfilelist[j]
			exebegin = time.time()
			ret = os.fork()
			if ret == 0:
				os.execl("gst","gst",tmpfilelist[i],tmpfilelist[j],str(i),str(j),"30")
			else:
				os.wait()
			exeend = time.time()
			print ("time:%.6f"%(exeend-exebegin))
			
	#		ret = os.fork()
	#		if ret == 0:
	#			os.execl("stat","stat",cppfilelist[i],cppfilelist[j])
	#		else:
	#			os.wait()
			#print GstLib.cgst(tmpfilelist[i],tmpfilelist[j])
			#something = raw_input("input something")
	
	print "end"

#if len(sys.argv) == 2:
#	fdir = sys.argv[1]
#else:
#	print 'Usage:%s <assignment-pathname>'%sys.argv[0]
#	sys.exit()
#if not os.path.exists(fdir):
#	print 'The path:%s is not exist!'%fdir
#	sys.exit()
#if os.path.isfile(fdir):
#	print 'The path:%s is a file,it should be a folder!'%fdir
#	sys.exit()
#
#PreProc(fdir)
#MainProc(fdir)
