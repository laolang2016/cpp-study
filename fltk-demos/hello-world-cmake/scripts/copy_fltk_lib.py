#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import os
import subprocess

if __name__ == '__main__':
	print('-- copy fltk libs')
	# 工程路径
	proj_path = sys.argv[1]
	# 构建路径
	build_path = sys.argv[2]
	# 构建后库存放路径
	lib_path = build_path + '/lib'
	# cmake FindFLTK 查找到的 fltk 库列表, 包含系统库
	fltk_cmake_libs = sys.argv[3]
	# 可执行程序名称
	app_name = sys.argv[4]

	# lib 目录不存在则创建
	if not os.path.exists(lib_path):
		os.makedirs(lib_path)

	# 过滤 fltk 库路径列表
	fltk_cmake_libs = fltk_cmake_libs.split(";")
	fltk_libs = []
	for lib in fltk_cmake_libs:
		if "fltk" in lib:
			fltk_libs.append(lib)
	# print(fltk_libs)

	# 执行 ldd , 查找可执行程序需要的 fltk 库
	ldd_command = 'ldd ' + build_path + '/bin/' + app_name
	status, ldd_res =subprocess.getstatusoutput(ldd_command)
	if 0 != status:
		print("ldd app failed", file = sys.stderr )
		exit(1)
	ldd_res = ldd_res.split("\n")
	need_fltk_libs = []
	for lib in ldd_res:
		if "fltk" in lib:
			need_fltk_libs.append(lib.split("=")[0].strip())
	# print(need_fltk_libs)

	# 复制 ftlk 到 lib 路径
	for lib_sys in fltk_libs:
		for lib_need in need_fltk_libs:
			lib_name = lib_need.split(".")[0] + ".so" 
			if lib_name in lib_sys:
				command = "cp " + lib_sys + " " + lib_path + "/" + lib_need
				print("-- " + command)
				status,_ = subprocess.getstatusoutput(command)
				if 0 != status:
					print("copy lib" + lib_name +"failed", file = sys.stderr )
					exit(1)
	