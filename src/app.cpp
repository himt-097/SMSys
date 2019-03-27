#include "app.h"


App::App() :
	user(nullptr) {
	user = new User();
	staff = new Staff();
	courses = new Courses();
}


App::~App() {
	delete user;
	delete staff;
	delete courses;
}


bool App::Login(string user_name, string password) {
	bool login_status = false;

	login_status = user->Login(user_name, password);

	// check role de cap phat instance
	staff = new Staff();

	return login_status;
}


bool App::Logout() {
	bool logout_status = false;

	logout_status = user->Logout();

	delete staff;
	return logout_status;
}


bool App::ImportClass(const string &class_name, const string &csv_name) {
	bool import_status = false;

	import_status = staff->ImportClass(class_name, csv_name);

	return import_status;
}


bool App::AddNewStudentToClass(const string &class_name, Student &new_student) {
	bool add_status = false;

	add_status = staff->AddNewStudentToClass(class_name, new_student);

	return add_status;
}


bool App::ChangeStudentFromClassAToB(const int &id, string &class_b) {
	bool change_status = false;

	change_status = staff->ChangeStudentFromClassAToB(id, class_b);

	return change_status;
}


bool App::RemoveStudentFromClass(const int &ID) {
	bool remove_status = false;

	remove_status = staff->RemoveStudentFromClass(ID);

	return remove_status;
}


bool App::EditStudentFromClass(Student &student) {
	bool edit_status = false;

	edit_status = staff->EditStudentFromClass(student);

	return edit_status;
}


Student App::GetStudent(const int &ID) {
	Student student = staff->GetStudent(ID);

	return student;
}


vector<string> App::GetClassList() {
	vector<string> class_list;
	
	class_list = staff->GetClassList();
	
	return class_list;
}


vector<Student> App::GetStudentListFromClass(string &class_name) {
	vector<Student> students_list;
	
	students_list = staff->GetStudentListFromClass(class_name);
	
	return students_list;
}


vector<string> App::GetCsvForClass() {
	vector<string> lists;

	lists = staff->GetCsvForClass();

	return lists;
}


bool App::ImportCourse(const string &course_id, const string &csv_name) {
	bool import_status;
	
	import_status = courses->ImportCourse(course_id, csv_name);

	return import_status;
}


bool App::AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2) {
	bool add_status;

	add_status = courses->AddNewCourse(new_course, class_name, number_period, period_1, period_2);

	return add_status;
}


bool App::AddStudentToCourse(const string &course_id, int student_id) {
	bool add_status = false;

	add_status = courses->AddStudentToCourse(course_id, student_id);

	return add_status;
}


bool App::RemoveStudentFromCourse(const string &course_id, int del_student) {
	bool remove_status = false;

	remove_status = courses->RemoveStudentFromCourse(course_id, del_student);

	return remove_status;
}


vector<string> App::GetCsvForCourse() {
	vector<string> lists;

	lists = staff->GetCsvForCourse();

	return lists;
}


vector<string> App::GetCourselist() {
	vector<string> courses_list;

	courses_list = staff->GetCourselist();

	return courses_list;
}


vector<Student> App::GetStudentListFromCourse(string &course_name) {
	vector<Student> students_list;

	students_list = staff->GetStudentListFromCourse(course_name);

	return students_list;
}

vector<Attendance> App::GetAttendanceList(string &course_name) {
	vector<Attendance> Attendance_list;

	Attendance_list = staff->GetAttendanceList(course_name);

	return Attendance_list;
}