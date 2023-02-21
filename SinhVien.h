#ifndef SINHVIEN_H
#define SINHVIEN_H
#include<iostream>
using namespace std;
class SinhVien{
	private:
		string id, fullName, classSv, addRess;
		double GPA;
	public:
		SinhVien(){
			this->id = "000000";
			this->fullName = "nul";
			this->classSv = "nul";
			this->addRess = "nul";
			this->GPA = 0;
		}
		string getId() const{
			return this->id;
		}
		string getFullName() const{
			return this->fullName;
		}
		string getClassSv() const{
			return this->classSv;
		}
		string getAddRess() const{
			return this->addRess;
		}
		double getGpa() const{
			return this->GPA;
		}
		void setId(string s){
			this->id  = s;
		}
		void setFullName(string fullName){
			this->fullName = fullName;
		}
		void setClassSv(string classSv){
			this->classSv = classSv;
		}
		void setAddress(string addRess){
			this->addRess = addRess;
		}
		void setGpa(double GPA){
			this->GPA = GPA;
		}
};
#endif
