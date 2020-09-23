#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class TextFile {
public:
	TextFile(string);
	TextFile();
	~TextFile();

	void open();
	void add_text(string);
	void save(string);
	void insert(string, int);
	const void print();
	string get_name();

	friend void open_text(TextFile&, string);
	friend void close_text(TextFile&);
	friend int get_file_size(TextFile&);
private:
	string name;
	string buff;
	FILE* file;
};

TextFile::TextFile(string fname):name(fname)
{
}
TextFile::TextFile():name("file.txt"), buff("")
{
}
TextFile::~TextFile() {
	cout << ":)" << endl;
}

void TextFile::open() {
	open_text(*this, name);

	int size = get_file_size(*this);
	char* temp_buff = new char[size + 1]();
	while (fgets(temp_buff, 256, file) != 0) {
		buff.append(string(temp_buff));
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

void TextFile::insert(string str, int n) {
	open_text(*this, name);
	buff.insert(n, str);
	char* temp_buff = new char[buff.length() + 1]();
	strcpy_s(temp_buff, buff.length() + 1, buff.c_str());
	fputs(temp_buff, file);
	delete temp_buff;
	close_text(*this);
}

const void TextFile::print() {
	cout << "\tFile name: " << name << endl;
	cout << buff << endl;
}

string TextFile::get_name() {
	return name;
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

void print_menu();
int get_variant(int&, int);

int main()
{
	int variant;

	cout << "Enter the name of the file you will work with. If such file doesn't exist, a new file would be created" << endl;
	cout << ">";
	string name;
	cin >> name;
	TextFile f(name);
	do {
		system("pause");
		print_menu();
		variant = get_variant(variant, 6);
		switch (variant) {
			case 1:
			{
				f.open();
				cout << "The file was opened" << endl;
				break;
			}
			case 2:
			{
				cout << "Enter the text you want to add to the end of the file: " << endl;
				cout << ">";
				string text;
				cin.ignore(32767, '\n');
				getline(cin, text);
				f.add_text(text);
				break;
			}
			case 3:
			{
				cout << "Enter the text you want to insert: " << endl;
				cout << ">";
				string text;
				cin.ignore(32767, '\n');
				getline(cin, text);
				cout << "Enter the index of the character to insert text in(the right part of the source text will be moved)" << endl;
				cout << ">";
				int i;
				cin >> i;
				while (i < 0) {
					cout << "Please enter valid index: " << endl;
					cin >> i;
				}
				f.insert(text, i);
				cout << "The text was inserted" << endl;
				break;
			}
			case 4:
			{
				cout << "Do you want to change file name?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;
				cout << ">";
				int variant = get_variant(variant, 2);
				switch (variant) {
				case 1:
				{
					cout << "Enter a new name: " << endl;
					string name;
					cin >> name;
					f.save(name);
					break;
				}
				case 2:
				{
					f.save(f.get_name());
					break;
				}
				}
				break;
			}
			case 5:
			{
				f.print();
				break;
			}
		}
	} while (variant != 6);

}

void print_menu() {
	system("cls");
	cout << "What do you want to do?" << endl;
	cout << "1. Open file" << endl;
	cout << "2. Add text to the end of the file" << endl;
	cout << "3. Insert text in the file" << endl;
	cout << "4. Save file with a specific name" << endl;
	cout << "5. Print the content of the file" << endl;
	cout << "6. Exit" << endl;
	cout << ">";
}

int get_variant(int& variant, int n) {
	cin >> variant;
	while (variant < 1 || variant > n) {
		cout << "Incorrect input. Try again." << endl;
		cin >> variant;
	}
	return variant;
}

