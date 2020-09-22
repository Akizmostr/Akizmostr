#include <iostream>
#include <string>
#include <string.h>

using namespace std;

/// <summary>
/// !!!!!!!!!!!!!!!!!!!ДОДЕЛАТЬ ФУНКЦИОНАЛ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// !!!!!!!!!!!!!!!!!!!ВСТАВКА СТРОКИ В ФАЙЛ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// !!!!!!!!!!!!!!!!!!
/// !!!!!!!!!!!!!!!!!!
/// !!!!!!!!!!!!!!!!!
/// </summary>

class TextFile {
public:
	TextFile(string);
	TextFile();
	~TextFile();

	void open();
	void add_text(string);
	void save(string);

	friend void open_text(TextFile&, string);
	friend void close_text(TextFile&);
	friend int get_file_size(TextFile&);
private:
	string name;
	string buff;
	FILE* file;
	int length;
};

TextFile::TextFile(string fname):name(fname) {
}
TextFile::TextFile() {
	name = "file.txt";
}
TextFile::~TextFile() {
}

void TextFile::open() {
	open_text(*this, name);
	int size = get_file_size(*this);
	char* temp_buff = new char[size+1]();
	fgets(temp_buff, size + 1, file);
	if (size!=0) {
		buff = string(temp_buff);
	}
	delete temp_buff;
	close_text(*this);
}

void TextFile::add_text(string str) {
	open_text(*this, name);
	buff.append(str);
	char* temp_buff = new char[buff.length() + 1]();
	strcpy_s(temp_buff,buff.length() + 1, buff.c_str());
	fputs(temp_buff, file);
	delete temp_buff;
	close_text(*this);
}

void TextFile::save(string newname) {
	if (newname==name) {
		open_text(*this, name);
	}
	else {
		rename(name.c_str(), newname.c_str());
		open_text(*this, newname);
	}
	close_text(*this);
}

void open_text(TextFile& file, string name) {
	errno_t err = fopen_s(&file.file, name.c_str(), "r+");
	if (err != 0) {
		cout << "Such file doesn't exist, creating a new file...\n";
		err = fopen_s(&file.file, name.c_str(), "w+");
		if (err == 0) {
			cout << "The file was created and opened\n";
		}
		else {
			cout << "Error: the file was not opened or created\n";
			exit(1);
		}
	}
}

void close_text(TextFile& file) {
	if (file.file) {
		errno_t err = fclose(file.file);
		if (err != 0) {
			cout << "Error: the file was not closed" << endl;
			exit(2);
		}
	}
	else {
		cout << "Error with the file" << endl;
		exit(3);
	}
}

int get_file_size(TextFile& file) {
	if (fseek(file.file, 0, SEEK_END) != 0) {
		cout << "Error while getting file size" << endl;
		exit(4);
	}

	long size = ftell(file.file);

	if (size == -1L) {
		cout << "Error while getting file size" << endl;
		exit(5);
	}

	rewind(file.file);

	return size;
}

int main()
{
	TextFile f("hello.txt");
	f.open();
	f.add_text("Hello Slavik x2");
	f.save("hello.txt");
}

