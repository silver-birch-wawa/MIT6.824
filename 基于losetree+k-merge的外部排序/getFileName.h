// 遍历文件夹下的文件，获取文件的段名和文件大小的信息
void getAllFileNames(priority_queue<fileinfo,vector<fileinfo>,cmp>&filesinfo,const string& folder_path)
{
	_finddata_t file;
	long flag;
	string filename = folder_path + "\\*";//遍历制定文件夹内的jpg文件
	if ((flag = _findfirst(filename.c_str(), &file)) == -1)//目录内找不到文件
	{
		cout << "There is no such type file" << endl;
	}
	else
	{
		//通过前面的_findfirst找到第一个文件.和第二个文件..
		string name = folder_path + "\\" + file.name;//file.name存放的是遍历得到的文件名
		//依次寻找以后的文件
        _findnext(flag, &file);
		while (_findnext(flag, &file) == 0)
		{
			string name = string(folder_path + "\\" + string(file.name));
			//cout << file.name << endl;
			fileinfo f;
			f.scope=atoi(file.name);
			f.size=txt_file_size(name.c_str());
			filesinfo.push(f);
		}
	}
	_findclose(flag);
}