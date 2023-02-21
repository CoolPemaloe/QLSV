#include"DoHoa.h"
#include"SinhVien.h"
#include<vector>
#include<iomanip>
#include<string>
#include<algorithm>
#include<fstream>
#include<ctype.h>
const int x = 5;
const int y = 2;
const int width = 86;
const int height = 30;
const int subx = 26;
const int suby = 8;
const int subw = 42;
const int subh = 2;
const string back = "ESC : back";
const int red = 4;
const int white = 7;
const int black = 0;
const int maxSize_outPut = 11; // Kich co in ra nhieu nhat
const char ARROW = 26;
int curPage = 1; // Trang hien tai
vector<SinhVien> sv;
void Box(int x, int y, int width, int height, int color);
void Board();
void Menu();
void exitScript();
void inPut(vector<SinhVien>& sv);
void outPut(vector<SinhVien> sv, int cur_Page_in);
void Board2();
void Menu2();
void getFirstSpace(string& str);
void chuanHoa(string& str);
void inPutInsert(vector<SinhVien>& sv, int pos);
bool cmp(SinhVien a, SinhVien b);
void leftControl(int dis = 0);
void rightControl(int dis = 0);
bool isInt(string s);
int strtoInt(string s);
bool isDouble(string str);
double stoDouble(string str);
void Menu3();
//-------------------------------------------------------
int main(){
	SetConsoleTitle("Quan Li Sinh Vien");
	resizeConsole(793, 570);
	SetScreenBufferSize(793, 570);
	DisableCtrButton(0, 0, 1);
	ShowScrollbar(0);
	DisableResizeWindow();	
	Menu();
	return 0;
}
//-------------------------------------------------------
void Box(int x, int y, int width, int height, int color) {
	
	for (int ix = x; ix <= x + width; ix++) {
		textcolor(color);
		gotoxy(ix, y);
		cout << char(196);
		gotoxy(ix, y + height);
		cout << char(196);
	}
	for (int iy = y; iy <= y + height; iy++) {
		gotoxy(x, iy);
		cout << char(179);
		gotoxy(x + width, iy);
		cout << char(179);
	}
	gotoxy(x, y); cout << char(218);
	gotoxy(x + width, y); cout << char(191);
	gotoxy(x, y + height); cout << char(192);
	gotoxy(x + width, y + height); cout << char(217);
	textcolor(white);

}
void Board() {
	//Border
	Box(x, y, width, height, red);
	string instruction = "ESC: exit";
	gotoxy(x + width - instruction.size() , y + height - 1);
	cout<<instruction;
	
	//Introduce
	Box(subx, suby, subw, subh, 14);
	gotoxy(subx + 13, suby + 1);
	textcolor(6);
	cout << "QUAN LI SINH VIEN";
	textcolor(white);
	
	int distance = 3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 15, suby + distance + 1);
	textcolor(13);
	cout << "NHAP DANH SACH";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 15, suby + distance + 1);
	textcolor(13);
	cout << "XUAT DANH SACH";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 11, suby + distance + 1);
	textcolor(13);
	cout << "LUU DANH SACH VAO FILE";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 11, suby + distance + 1);
	textcolor(13);
	cout << "NHAP DANH SACH TU FILE";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 19, suby + distance + 1);
	textcolor(13);
	cout << "KHAC "<<char(16);
}
void Menu(){
	int distance = 3;
	const int lowerLimit = distance*2;
	int numberofBox = 5;
	const int upperLimit = distance*(numberofBox-1);
	while(true){
		Nocursortype();
		Board();
		Box(subx, suby + distance, subw, subh, 10);
		gotoxy(subx-1, suby + distance + 1);	
		textcolor(red);
		cout<<ARROW;
		textcolor(white);
		char movePtr = getch();
		
		if(movePtr == 72 && distance >= lowerLimit){
			gotoxy(subx-1, suby + distance + 1);
			textcolor(black);
			cout<<ARROW;
			distance-=3;
		}
			
		if(movePtr == 80 && distance <= upperLimit){
			gotoxy(subx-1, suby + distance + 1);
			textcolor(black);
			cout<<ARROW;
			distance+=3;
		}
		
		//Enter
		if(movePtr == 13){
			if(distance == 3){
				inPut(sv);
			}
			else if(distance == 6){
				outPut(sv, curPage);
			}
			else if(distance == 9){
				if(sv.size() == 0){
					system("cls");
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-12, (y + height)/2);
					cout<<"CHUA NHAP THONG TIN CHO SINH VIEN";
					gotoxy(x + width - back.size(), y + height-1);
					cout<<back;
					Sleep(400);
					system("cls");
				}
				else{
					ofstream fileOut("data.txt", ios_base::out);
					fileOut<<sv.size()<<endl;
					for(int i=0;i<sv.size();i++){
						fileOut<<sv[i].getId()<<","<<endl;
						fileOut<<sv[i].getFullName()<<","<<endl;
						fileOut<<sv[i].getClassSv()<<","<<endl;
						fileOut<<sv[i].getAddRess()<<","<<endl;
						fileOut<<sv[i].getGpa();
						if(i<sv.size()-1)
							fileOut<<endl;
					}
					
					system("cls");
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-8, (y + height)/2);
					cout<<"NHAP DU LIEU THANH CONG";
					gotoxy(x + width - back.size(), y + height-1);
					cout<<back;
					Sleep(400);
					system("cls");
					
					fileOut.close();
				}						
			}
			else if(distance == 12){
				ifstream fileIn("data.txt", ios_base::in);
				if(fileIn.fail()){
					ofstream fileOut("data.txt", ios_base::out);
					system("cls");
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-8, (y + height)/2);
					cout<<"DA TAO THU MUC LUU TRU";
					gotoxy((x + width)/2-20, (y + height)/2+2);
					cout<<"FILE R^NG~ - VUI LONG LUU THONG TIN VAO FILE TRUOC";
					gotoxy(x + width - back.size(), y + height-1);
					cout<<back;
					getch();
					system("cls");
					fileOut.close();
				}
				else{
					system("cls");
					int size_block_Data = 0;
					fileIn>>size_block_Data;
					if(size_block_Data == 0){
						
						Box(x, y, width, height, red);
						gotoxy((x + width)/2-8, (y + height)/2);
						cout<<"KHONG CO DU LIEU TRONG FILE";
						gotoxy(x + width - back.size(), y + height-1);
						cout<<back;
						Sleep(800);
						system("cls");
						
					}
					else{
						sv.clear();
						Box(x, y, width, height, red);
						gotoxy((x + width)/2-8, (y + height)/2);
						cout<<"DANG XOA DU LIEU CU";
						gotoxy(x + width - back.size(), y + height-1);
						cout<<back;
						Sleep(300);
						system("cls");
						
						SinhVien svTmp;
						for(int i=0;i<size_block_Data;i++){
							string tmp;
							getline(fileIn, tmp,',');
							getFirstSpace(tmp);
							svTmp.setId(tmp);
							
							getline(fileIn, tmp,',');
							getFirstSpace(tmp);
							svTmp.setFullName(tmp);
							
							getline(fileIn, tmp,',');
							getFirstSpace(tmp);
							svTmp.setClassSv(tmp);
							
							getline(fileIn, tmp,',');
							getFirstSpace(tmp);
							svTmp.setAddress(tmp);
							
							double gpa;
							fileIn>>gpa;
							svTmp.setGpa(gpa);
							
							sv.push_back(svTmp);
						}
						
						Box(x, y, width, height, red);
						gotoxy((x + width)/2-8, (y + height)/2);
						cout<<"DA NHAP DU LIEU THANH CONG";
						gotoxy(x + width - back.size(), y + height-1);
						cout<<back;
						Sleep(400);
						system("cls");
						
					}
				}
				fileIn.close();
			}
			else{
				system("cls");
				Menu2();
				system("cls");
			}
		}
		
		//ESC
		if(movePtr == 27){
			exitScript();
			break;
		}
	}
}
void exitScript(){
	system("cls");
	gotoxy(40, 5);
	cout<<"---Exit---";
	cout<<"\n\n\n";
}
void inPut(vector<SinhVien>& sv){
	system("cls");
	Box(x, y, width, height, red);
	
	int sizeList;
	
	do{
		int distance = 0;
		Box(subx, suby + distance, subw, subh, 3);
		gotoxy(subx + 10, suby + 1 + distance);
		cout<<"NHAP THONG TIN SINH VIEN";
		
		distance += 5;
		Box(subx, suby + distance, subw, subh + distance , 3);
		gotoxy(subx + 10, suby + 1 + distance);
		cout<<"-NHAP SO LUONG SINH VIEN-";
		gotoxy(subx + 21, suby + 3 + distance);
		Yescursortype();
		string tmp;
		getline(cin, tmp);
		sizeList = strtoInt(tmp);
		Nocursortype();
	}
	while(sizeList<=0);
	fflush(stdin);
	system("cls");	
	Box(x, y, width, height, red);
	
	SinhVien tmp;
	
	for(int i=0;i<sizeList;i++){
		fflush(stdin);
		int distance2 = 0;
		Box(subx, suby + distance2, subw, subh, 3);
		gotoxy(subx + 13, suby + 1);
		cout<<"SINH VIEN THU "<<i+1;
		distance2 += 5;
		Box(subx - 2, suby + distance2, subw + distance2-1, subh + distance2*2, 3);
		
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP MA SO SINH VIEN: ";
		Yescursortype();
		string id;getline(cin, id);
		Nocursortype();
		chuanHoa(id);
		tmp.setId(id);
		
		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP HO VA TEN: ";
		Yescursortype();
		string name;getline(cin, name);
		Nocursortype();
		chuanHoa(name);
		tmp.setFullName(name);

		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP LOP: ";
		Yescursortype();
		string svClass;getline(cin, svClass);
		Nocursortype();
		chuanHoa(svClass);
		tmp.setClassSv(svClass);
		
		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP DIA CHI: ";
		Yescursortype();
		string address;getline(cin, address);
		Nocursortype();
		chuanHoa(address);
		tmp.setAddress(address);
		
		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP GPA: ";
		Yescursortype();
		string gpaStr;
		getline(cin, gpaStr);
		Nocursortype();
		tmp.setGpa(stoDouble(gpaStr));
		
		sv.push_back(tmp);
		system("cls");
	}
	
	Box(x, y, width, height, red);
	gotoxy((x + width)/2-10, (y + height)/2);
	cout<<"NHAP THONG TIN THANH CONG!";
	gotoxy(x + width - back.size(), y + height-1);
	cout<<back;
	Sleep(400);
	system("cls");
}
void outPut(vector<SinhVien> sv, int curPage){
	system("cls");
	Box(x, y, width, height, red);
	if(sv.size() == 0){
		gotoxy((x + width)/2 - 12, (y + height)/2);
		cout<<"RO^NG~ - CAN NHAP THONG TIN TRUOC";
		gotoxy(x + width - back.size(), y + height-1);
		cout<<back;
		Sleep(500);
		system("cls");
		return;
	}
	
	int newX = x+2, newY = y+2, newW = width - 4, newH = height - 4;
	
	while(true){
		int page = 1;
		if(sv.size() > maxSize_outPut){
			page = sv.size() / maxSize_outPut;
			page = sv.size() % maxSize_outPut == 0 ? page : page + 1;
		}			
		if(sv.size() <= maxSize_outPut){
			Box(newX, newY, newW, newH, white);
			int hei = 2;
			gotoxy(newX+2, newY + hei);
			int wStt = 3, wId = 8, wName = 22, wClass = 14, wAddress = 14, wGpa = 12;
			cout<<setw(wStt)<<"STT"<<setw(wId)<<"ID"<<setw(wName)<<"HO VA TEN"<<setw(wClass)<<"LOP"<<setw(wAddress)<<"DIA CHI"<<fixed<<setprecision(1)<<setw(wGpa)<<"GPA";
			for(int i=0;i<sv.size();i++){
				hei+=2;
				gotoxy(newX+2, newY + hei);
				cout<<setw(wStt-1)<<i+1<<setw(wId+5)<<sv[i].getId()<<setw(wName)<<sv[i].getFullName()<<setw(wClass-1)<<sv[i].getClassSv()<<setw(wAddress-3)<<sv[i].getAddRess()<<setw(wGpa-2)<<sv[i].getGpa();
			}
			gotoxy(x + width - back.size(), y + height-1);
			cout<<back;
		}
		else{
			if(curPage == 1){
				system("cls");
				Box(x, y, width, height, red);
				Box(newX, newY, newW, newH, white);
				int hei = 2;
				gotoxy(newX+2, newY + hei);
				int wStt = 3, wId = 8, wName = 22, wClass = 14, wAddress = 14, wGpa = 12;
				cout<<setw(wStt)<<"STT"<<setw(wId)<<"ID"<<setw(wName)<<"HO VA TEN"<<setw(wClass)<<"LOP"<<setw(wAddress)<<"DIA CHI"<<fixed<<setprecision(1)<<setw(wGpa)<<"GPA";
				for(int i=0;i<maxSize_outPut;i++){
					hei+=2;
					gotoxy(newX+2, newY + hei);
					cout<<setw(wStt-1)<<i+1<<setw(wId+5)<<sv[i].getId()<<setw(wName)<<sv[i].getFullName()<<setw(wClass-1)<<sv[i].getClassSv()<<setw(wAddress-3)<<sv[i].getAddRess()<<setw(wGpa-2)<<sv[i].getGpa();
				}
				gotoxy(x + width - back.size(), y + height-1);
				cout<<back;			
				rightControl(1);
				cout<<" NEXT";
				
			}
			else{
				system("cls");			
				int curPage_begin = (curPage - 1)*maxSize_outPut;
				int curPage_end = curPage*maxSize_outPut;
				if(sv.size()%maxSize_outPut !=0)
					curPage_end = curPage < page ? curPage_end : (curPage - 1)*maxSize_outPut + sv.size()%maxSize_outPut;
				Box(x, y, width, height, red);
				Box(newX, newY, newW, newH, white);
				int hei = 2;
				gotoxy(newX+2, newY + hei);
				int wStt = 3, wId = 8, wName = 22, wClass = 14, wAddress = 14, wGpa = 12;
				cout<<setw(wStt)<<"STT"<<setw(wId)<<"ID"<<setw(wName)<<"HO VA TEN"<<setw(wClass)<<"LOP"<<setw(wAddress)<<"DIA CHI"<<fixed<<setprecision(1)<<setw(wGpa)<<"GPA";
				for(int i=curPage_begin;i<curPage_end;i++){
					hei+=2;
					gotoxy(newX+2, newY + hei);
					cout<<setw(wStt-1)<<i+1<<setw(wId+5)<<sv[i].getId()<<setw(wName)<<sv[i].getFullName()<<setw(wClass-1)<<sv[i].getClassSv()<<setw(wAddress-3)<<sv[i].getAddRess()<<setw(wGpa-2)<<sv[i].getGpa();
				}
				gotoxy(x + width - back.size(), y + height-1);
				cout<<back;	
				leftControl(1);
				
				if(curPage < page)
					rightControl(3);
			
			}
		}
		
		bool checkEnd = false;
		int press = getch();
		if(press == 27){
			system("cls");
			curPage = 1;
			return;
		}
		
		if(press == 77 && curPage < page)
			curPage++;
		
		if(press == 75 && curPage >=2)
			curPage--;
		
	}
}
void Board2() {
	//Border
	Box(x, y, width, height, red);
	string instruction = "ESC: exit";
	gotoxy(x + width - instruction.size() , y + height - 1);
	cout<<instruction;
	
	//Introduce
	Box(subx, suby, subw, subh, 14);
	gotoxy(subx + 13, suby + 1);
	textcolor(6);
	cout << "QUAN LI SINH VIEN";
	textcolor(white);
	
	int distance = 3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 15, suby + distance + 1);
	textcolor(13);
	cout << "XOA DANH SACH";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 13, suby + distance + 1);
	textcolor(13);
	cout << "XOA MOT SINH VIEN";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 14, suby + distance + 1);
	textcolor(13);
	cout << "CHEN SINH VIEN";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 13, suby + distance + 1);
	textcolor(13);
	cout << "SAP XEP THEO GPA";
	
	distance+=3;
	Box(subx, suby + distance, subw, subh, 9);
	gotoxy(subx + 17, suby + distance + 1);
	textcolor(13);
	cout<<char(17)<<" TRO VE";
}
void Menu2(){
	int distance = 3;
	const int lowerLimit = distance*2;
	int numberofBox = 5;
	const int upperLimit = distance*(numberofBox-1);
	while(true){
		Board2();
		Box(subx, suby + distance, subw, subh, 10);
		gotoxy(subx-1, suby + distance + 1);	
		textcolor(red);
		cout<<ARROW;
		textcolor(white);
		char movePtr = getch();
		
		if(movePtr == 72 && distance >= lowerLimit){
			gotoxy(subx-1, suby + distance + 1);
			textcolor(black);
			cout<<ARROW;
			distance-=3;
		}
			
		if(movePtr == 80 && distance <= upperLimit){
			gotoxy(subx-1, suby + distance + 1);
			textcolor(black);
			cout<<ARROW;
			distance+=3;
		}
		
		//Enter
		if(movePtr == 13){
			if(distance == 3){
				//XOA DANH SACH
				system("cls");
				sv.clear();
				Box(x, y, width, height, red);
				gotoxy((x + width)/2-5, (y + height)/2);
				cout<<"DA XOA DU LIEU";
				gotoxy(x + width - back.size(), y + height-1);
				cout<<back;
				Sleep(1000);
				system("cls");
			}
			else if(distance == 6){
				//XOA 1 SINH VIEN
				if(sv.size() != 0){
					int pos_Delete;
					do{
						fflush(stdin);
						system("cls");
						Box(x, y, width, height, red);
						Box(subx, suby + distance, subw, subh + distance , 3);
						gotoxy(subx + 10, suby + 1 + distance);
						cout<<"-NHAP VI TRI MUON XOA-";
						gotoxy(subx + 21, suby + 3 + distance);
						Yescursortype();
						string tmp;
						getline(cin, tmp);
						pos_Delete = strtoInt(tmp);
						Nocursortype();
					}
					while(pos_Delete>sv.size() || pos_Delete < 1);
					system("cls");
					
					pos_Delete-=1;
					sv.erase(sv.begin() + pos_Delete);
					
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-5, (y + height)/2);
					
					cout<<"XOA THANH CONG";
					
					gotoxy(x + width - back.size(), y + height-1);
					cout<<back;
					
					Sleep(800);
					system("cls");
				}
				else{
					system("cls");
					
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-5, (y + height)/2);
					
					cout<<"DANH SACH RONG";
					
					Sleep(500);
					system("cls");
				}
			}
			else if(distance == 9){
				//CHEN 1 SINH VIEN
				int pos_Insert;
				do{
					fflush(stdin);
					system("cls");
					Box(x, y, width, height, red);
					Box(subx, suby + distance, subw, subh + distance , 3);
					gotoxy(subx + 10, suby + 1 + distance);
					cout<<"-NHAP VI TRI MUON CHEN-";
					gotoxy(subx + 21, suby + 3 + distance);
					Yescursortype();
					string tmp;
					getline(cin, tmp);
					pos_Insert = strtoInt(tmp);
					Nocursortype();
				}
				while(pos_Insert > sv.size() + 1 || pos_Insert < 1);
				
				inPutInsert(sv, pos_Insert-1);
				
			}
			else if(distance == 12){
				//SAP XEP THEO GPA
				if(sv.size() == 0){

					system("cls");
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-5, (y + height)/2);
					cout<<"DANH SACH RONG";
					gotoxy(x + width - back.size(), y + height-1);
					cout<<back;
					Sleep(400);
					system("cls");
					
				}
				else{
					
					system("cls");
					if(sv.size() > 1)
						sort(sv.begin(), sv.end(), cmp);
					Box(x, y, width, height, red);
					gotoxy((x + width)/2-5, (y + height)/2);
					cout<<"SAP XEP THANH CONG";
					gotoxy(x + width - back.size(), y + height-1);
					cout<<back;
					Sleep(400);
					system("cls");
					
				}
			}
			else{
				//TRO VE MENU 1
				break;
			}
		}
		
		//TRO VE MENU 1
		if(movePtr == 27){
			break;
		}
	}
}
void getFirstSpace(string& str){
	if(str.size() == 0) return;
	if(str[0] == '\n' && str.size() > 1 ){
		for(int i=0;i<str.size()-1;i++){
			str[i]=str[i+1];
		}
		str.pop_back();
	}
}
void chuanHoa(string& str){
	for(int i=0;i<str.size();i++)
		str[i]=toupper(str[i]);
}
void inPutInsert(vector<SinhVien>& sv, int pos){
	system("cls");
	
	Box(x, y, width, height, red);
	
	int sizeList;
	
	do{
		int distance = 0;
		Box(subx, suby + distance, subw, subh, 3);
		gotoxy(subx + 10, suby + 1 + distance);
		cout<<"NHAP THONG TIN SINH VIEN";
		
		distance += 5;
		Box(subx, suby + distance, subw, subh + distance , 3);
		gotoxy(subx + 5, suby + 1 + distance);
		cout<<"-NHAP SO LUONG SINH VIEN CAN CHEN-";
		gotoxy(subx + 21, suby + 3 + distance);
		Yescursortype();
		string tmp;
		getline(cin, tmp);
		sizeList = strtoInt(tmp);
		Nocursortype();
	}
	while(sizeList<=0);
	fflush(stdin);
	system("cls");	
	Box(x, y, width, height, red);
	
	SinhVien tmp;
	
	for(int i=0;i<sizeList;i++){
		fflush(stdin);
		int distance2 = 0;
		Box(subx, suby + distance2, subw, subh, 3);
		gotoxy(subx + 13, suby + 1);
		cout<<"SINH VIEN THU "<<i+1;
		distance2 += 5;
		Box(subx - 2, suby + distance2, subw + distance2-1, subh + distance2*2, 3);
		
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP MA SO SINH VIEN: ";
		Yescursortype();
		string id;getline(cin, id);
		Nocursortype();
		chuanHoa(id);
		tmp.setId(id);
		
		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP HO VA TEN: ";
		Yescursortype();
		string name;getline(cin, name);
		Nocursortype();
		chuanHoa(name);
		tmp.setFullName(name);

		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP LOP: ";
		Yescursortype();
		string svClass;getline(cin, svClass);
		Nocursortype();
		chuanHoa(svClass);
		tmp.setClassSv(svClass);
		
		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP DIA CHI: ";
		Yescursortype();
		string address;getline(cin, address);
		Nocursortype();
		chuanHoa(address);
		tmp.setAddress(address);
		
		distance2+=2;
		gotoxy(subx, suby + 1 + distance2);
		cout<<"-NHAP GPA: ";
		Yescursortype();
		string gpaStr;
		getline(cin, gpaStr);
		Nocursortype();
		tmp.setGpa(stoDouble(gpaStr));
		
		sv.insert(sv.begin() + pos + i, tmp);
		system("cls");
	}
	
	Box(x, y, width, height, red);
	gotoxy((x + width)/2-10, (y + height)/2);
	cout<<"NHAP THONG TIN THANH CONG!";
	gotoxy(x + width - back.size(), y + height-1);
	cout<<back;
	Sleep(300);
	system("cls");
}
bool cmp(SinhVien a, SinhVien b){
	if(a.getGpa() != b.getGpa()) return a.getGpa() > b.getGpa();
	return a.getId() < b.getId();
}
void leftControl(int dis){
	gotoxy(x + dis, y + height - 1);
	cout<<char(17);
}
void rightControl(int dis){
	gotoxy(x + dis, y + height - 1);
	cout<<char(16);
}
bool isInt(string s){
	for(int i=0;i<s.size();i++)
		if(!isdigit(s[i])) return false;
	return true;
}
int strtoInt(string s){
	if(isInt(s) == false) return 0;
	int ans = 0;
	for(int i=0;i<s.size();i++){
		ans*=10;
		ans+=s[i]-'0';
	}
	return ans;
}
bool isDouble(string str){
	int cnt=0;
	for(int i=0;i<str.size();i++){
		if(!isdigit(str[i]) && str[i] == '.' && i!= 0 && i!=str.size()-1) 
			cnt++;
		if(!isdigit(str[i]) && str[i] != '.') return false;
	}
	if(cnt > 1) return false;
	return true;
}
double stoDouble(string str){
	double intergerPart=0;
	double tail = 0;
	if(isDouble(str)){
		int i;
		for(i=0;i<str.size();i++)
			if(str[i] != '.'){
				intergerPart*=10;
				intergerPart+= str[i]-'0';
			}
			else break;
		int n=10;
		for(int j=i+1;j<str.size();j++){
			double tmp = str[j]-'0';
			tail+=tmp/n;
			n*=10;
		}
	}
	return intergerPart + tail;
}
