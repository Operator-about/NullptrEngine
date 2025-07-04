#include<LoadFileComponents.h>


vector<string> LoadFile(string File) 
{
	ifstream In(File, ios::binary);
	if(In)
	{
		string Contents;
		In.seekg(0, ios::end);
		Contents.resize(In.tellg());
		In.seekg(0, ios::beg);
		In.read(&Contents[0], Contents.size());
		In.close();
		vector<string> OutContent;
		OutContent.push_back(Contents);
		return(OutContent);
	}
}