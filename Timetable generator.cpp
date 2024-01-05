#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <string>
#include<sstream>

using namespace std;

class Teacher
{
	string name;
	string ID;
	public:
		Teacher ()
		{
		}
		Teacher(string name, string id)
		{
			this->name = name;
			this->ID = id;
		}
	void setteacherinfo() 
	{
		cout << "Enter Teacher Name : ";
		cin >> name;
		cout << "Enter Teacher ID : ";
		cin >> ID;
		
	}
	string getname()
	{
		return name;
	}
};

class Course
{
	string name;
	int code;
	int creditHour;
	
	public:
		Teacher* teachers;
		Course (){
		}
		Course(string name, int code, int ch, Teacher *t): teachers(t)
		{
			this->name = name;
			this->code = code;
			this->creditHour = ch;
		}
	void setcourse(Teacher* teacher, int count) {
		int temp;
		cout << "Enter Course Name : ";
		cin >> name;
		cout << "Enter Course Code : ";
		cin >> code;
		cout << "Enter Course Credit Hours : ";
		cin >> creditHour;
		cout << "Please Select a teacher for this Course" << endl;
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << " : " << teacher[i].getname() << endl;
		}
		cin >> temp;
		teachers = &teacher[temp-1];
		
	}
	int getCreditHour()
	{
		return creditHour;
	}

	string getname()
	{
		return name;
	}

	int getcode()
	{
		return code;
	}

	Teacher* getTeachers()
	{
		return teachers;
	}~Course()
	{
		delete teachers;
	}
};

class Room
{
	string number;
	public:
		Room (){
		}
		Room(string n): number(n) {}
	void fillroomdetails(int num)
	{
		stringstream ss;
        ss << num;
        number = "A" + ss.str();
		
		cout << "Room Generated----- Room Number : " << number << endl;
	}
	string getnumber()
	{
		return number;
	}

	friend class Course;
};

class Class
{
	string name;
	Course* courses;
	int num_courses;
	public:
		Class ()
		{
		}
		Class(string name, Course *cs[], int num_cs)
	{
		this->name = name;
		this->num_courses = num_cs;
	}
	void setclassinfo(Course* course,int subject)
	{
		cout << "Enter Section Name : ";
		cin >> name;
		cout << "Enter the amount of courses you want to allocate : " ;
		cin >> num_courses;
		courses = new Course[num_courses];
		for (int j = 0; j < num_courses ; j++)
		{
		for (int i = 0; i < subject; i++)
		{
			cout << i + 1 << " : " <<course[i].getname() << "\t" << "Teacher : " << course[i].teachers->getname()<< endl;
		}
		int temp;
		cout << "Select a suitable course" << endl;
		cin >> temp;
		courses[j] = course[temp-1];
	}
}
	Course *getcourses()
	{
		return courses;
	}
	
	int getnum_courses()
	{
		return num_courses;
	}

	string getname()
	{
		return name;
	}~Class()
	{
		delete[] courses;
	}
};

class Timetable
{
	Class *classes;
	int num_classes;
	Room *rooms;
	int num_rooms;
	public:
		Timetable(Class* c, int num_c, Room* r, int num_r ): classes(c), rooms(r)
	{
		num_classes = num_c;
		num_rooms = num_r;
	}

	void generate()
	{
		int time;
		cout << "How Many Slots would you like to alot in one day (1 class lasts 1 hour): ";
		cin >> time;
		int i, j, k;
		int total_creditHour = 0;
		//Checking if time table is possible
		for (i = 0; i < num_classes; ++i)
		{
			for (j = 0; j < classes[i].getnum_courses(); ++j)
			{
				Course *course = &classes[i].getcourses()[j];
				total_creditHour += course->getCreditHour();
			}
		}

		if (num_rooms *time * 5 < total_creditHour)
		{
			cout << "No. of rooms are less than the classes, increase No.of rooms to print time table\n";
		}
		else
		{
			//calculating credit hour of each class
			int creditHour[num_classes];
			for (i = 0; i < num_classes; ++i)
				creditHour[i] = 0;
			for (i = 0; i < num_classes; ++i)
			{
				for (j = 0; j < classes[i].getnum_courses(); ++j)
				{
					Course *course = &classes[i].getcourses()[j];
					creditHour[i] += course->getCreditHour();
				}
			}
			int day = 5;//5 days in a week
			int timetable[num_classes][day][time];
			//Initializing all elements of time table to -1 (indicating no class scheduled)
			for (i = 0; i < num_classes; ++i)
			{
				for (j = 0; j < 5; ++j)
				{
					for (k = 0; k < time; ++k)
					{
						timetable[i][j][k] = -1;
					}
				}
			}

			string tt[num_classes][day][time];
			string Rooms[num_rooms][day][time];
			// Scheduling classes in the time table
			for (i = 0; i < num_classes; ++i)
			{
			    for (j = 0; j < classes[i].getnum_courses(); ++j)
			    {
			        Course *course = &classes[i].getcourses()[j];
			        int credithour = course->getCreditHour();
			        for (k = 0; k < credithour; ++k)
			        {
			            int x = rand() % day;
			            int hour = rand() % time;
			            while (timetable[i][x][hour] != -1)
			            {
			                x = rand() % day;
			                hour = rand() % time;
			            }
			            // Select a random room
			            int roomIndex = rand() % num_rooms;
			            // Assign room to the scheduled class
			            timetable[i][x][hour] = course->getcode();
			
			            Teacher *teacher = course->getTeachers();
			            tt[i][x][hour] = course->getname() + "\t" + teacher->getname() + "\t" + rooms[roomIndex].getnumber();
			        }
			    }
			}
			//Printing time table
			for (i = 0; i < num_classes; ++i)
			{
				cout << "Time Table for Class " << classes[i].getname() << endl;
				cout << "--------------------------------------------\n";
				cout << "Day\tTime Slot\tCourse\tTeacher\tRoom\n";
				cout << "--------------------------------------------\n";
				for (j = 0; j < 5; ++j)
				{
					for (k = 0; k < time; ++k)
					{
						string day;
						switch (j)
						{
							case 0:
								day = "Mon";
								break;
							case 1:
								day = "Tue";
								break;
							case 2:
								day = "Wed";
								break;
							case 3:
								day = "Thu";
								break;
							case 4:
								day = "Fri";
								break;
						}

						if (timetable[i][j][k] != -1)
						{
							int index = timetable[i][j][k];
							cout << day << "\t" << k + 1 << "\t\t" << tt[i][j][k] << endl;
						}
					}
				}
				cout << endl;
			}
		}
	}
};

main()
{
	cout << "\tWELCOME TO THE TIMETABLE GENERATOR\n\n" << endl;
	Teacher* teacher;
	Course* course;
	Room*	room;
	Class* classes;
	int faculty;
	cout << "Enter the amount of teachers you want to assign : ";
	cin >> faculty;
	teacher = new Teacher[faculty];
	for (int i = 0; i < faculty; i++)
	{
		teacher[i].setteacherinfo();
	}
	int subject;
	cout << "Enter the amount Coursese being taught : ";
	cin >> subject;
	course = new Course[subject];
	for (int i = 0; i < subject; i++)
	{
		course[i].setcourse(teacher, faculty);
	}
	int rooms;
	cout << "Enter the amount of rooms to allocate : ";
	cin >> rooms;
	room = new Room[rooms];
	for (int i = 0; i < rooms; i++)
	{
		room[i].fillroomdetails(i+1);
	}
	int cl;
	cout << "Enter the amount of sections you want to create : ";
	cin >> cl;
	classes = new Class[cl];
	for (int i = 0; i < cl; i++)
	{
		classes[i].setclassinfo(course,subject);
	}
	
	Timetable timetable(classes, cl, room, rooms);
	timetable.generate();

}
