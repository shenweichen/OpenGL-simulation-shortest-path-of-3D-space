# 配置说明
`GLUT`不是`OpenGL`所必须的，但它会给我们的学习带来一定的方便，推荐安装。 
Windows环境下的GLUT下载地址：（大小约为150k） 
http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip 

# Windows环境下安装GLUT的步骤： 

1. 将下载的压缩包解开，将得到5个文件 
2. 在“我的电脑”中搜索“gl.h”，并找到其所在文件夹（如果是VisualStudio2005，则应该是其安装目录下面的“VC/PlatformSDK/include/gl文件夹”）。把解压得到的glut.h放到这个文件夹。 
3. 把解压得到的glut.lib和glut32.lib放到静态函数库所在文件夹（如果是VisualStudio2005，则应该是其安装目录下面的“VC/lib”文件夹）。
4. 把解压得到的glut.dll和glut32.dll放到操作系统目录下面的system32文件夹内。（典型的位置为：C:/Windows/System32） 