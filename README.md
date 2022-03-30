# getfileList
获取文件列表的工具，可以获取指定目录下的所有文件（包括子目录里面的文件）的绝对路径及MD5。
返回的内容直接以类似Json的格式输出到命令行了。
请自行移除绝对路径，json格式里面多余的逗号。
请自行对斜杠和反和斜杠进行处理，
    libcurl里面下载链接需要的是斜杠/，反斜杠\可能会导致访问不了等。win系统的路径一般是反斜杠，但是正斜杠也行。
    json格式的字符串反斜杠最好用双反斜杠，避免转移导致反斜杠丢失。
    
其他问题请自行修改。