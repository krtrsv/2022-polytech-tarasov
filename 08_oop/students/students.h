#include <cstring>
#include <initializer_list>
#include <iostream>

struct Student {
  const char *name;
  int score;

  friend std::ostream &operator<<(std::ostream &out, Student &s) {
    out << "{name: \"" << s.name << "\", score: " << s.score << "}";
    return out;
  }

  const bool operator==(const Student &s) const {
    return !(std::strcmp(name, s.name)) && score == s.score;
  }

  const bool operator!=(const Student &s) const { return !(*this == s); }
};

class StudentList {
private:
  Student *students;
  int length;

  StudentList& _set_score(const char *n, int ns) {
    for (int i = 0; i < length; ++i) {
      if (!std::strcmp(students[i].name, n)) {
        students[i].score = ns;
        return *this;
      }
    }
    return *this;
  }

  StudentList& _remove(const char *n) {
    for (int i = 0; i < length; ++i) {
      if (!std::strcmp(students[i].name, n)) {
        for (int x = i; x < length - 1; ++x)
          students[x] = students[x + 1];
        Student *tmp =
            (Student *)std::realloc(students, (length - 1) * sizeof(Student));
        if (tmp == NULL && length > 1)
          exit(EXIT_FAILURE);
        length--;
        students = tmp;
        return *this;
      }
    }
    return *this;
  }

public:
  StudentList() {
    students = {};
    length = 0;
  }

  StudentList(std::initializer_list<Student> s) {
    length = s.size();
    if (!length)
      StudentList();
    students = (Student *)std::realloc(students, length * sizeof(Student));
    for (int i = 0; i != length; ++i)
      students[i] = s.begin()[i];
  }

  StudentList(const StudentList &other) {
    length = other.length;
    students = (Student *)std::realloc(students, length * sizeof(Student));
    for (int i = 0; i != length; ++i)
      students[i] = other.students[i];
  }

  StudentList &operator=(const StudentList &other) {
    if (this == &other)
      return *this;
    length = other.length;
    students = (Student *)std::realloc(students, length * sizeof(Student));
    for (int i = 0; i != length; ++i)
      students[i] = other.students[i];
    return *this;
  }

  /// Append `Student` object to students array
  StudentList &append(Student &s) {
    students =
        (Student *)std::realloc(students, (length + 1) * sizeof(Student));
    students[length] = s;
    length++;
    return *this;
  }

  /// Remove first occurance of student in students array
  StudentList &remove(const char *n) { return _remove(n); }
  StudentList &remove(Student &s) { return _remove(s.name); }

  /// Set score of student
  StudentList &set_score(const char *n, int ns) { return _set_score(n, ns); }
  StudentList &set_score(Student &sl, int ns) { return _set_score(sl.name, ns); }

  /// Get average score of students
  double get_avg_score() const {
    double score_sum = 0;
    for (int i = 0; i < length; ++i) {
      score_sum += students[i].score;
    }
    return score_sum / length;
  }

  Student find_student(const char *n) {
    for (int i = 0; i < length; ++i) {
      if (!std::strcmp(students[i].name, n)) {
        return students[i];
      }
    }
    return Student{};
  }

  /// Get array of students with score >6
  StudentList get_best_students() const {
    StudentList best_students{};
    for (int i = 0; i < length; ++i) {
      if (students[i].score > 6) {
        best_students.append(students[i]);
      }
    }
    return best_students;
  }

  /// Get array of students with score <4
  StudentList get_worst_students() const {
    StudentList worst_students{};
    for (int i = 0; i < length; ++i) {
      if (students[i].score < 4) {
        worst_students.append(students[i]);
      }
    }
    return worst_students;
  }

  friend std::ostream &operator<<(std::ostream &out, StudentList &sl) {
    if (sl.length == 0) {
      out << "[]";
      return out;
    }
    out << "[\n";
    for (int i = 0; i < sl.length; ++i) {
      out << "  " << sl.students[i];
      if (i + 1 != sl.length)
        out << ", \n";
    }
    out << "\n]";
    return out;
  }

  const bool operator==(const StudentList &sl) const {
    if (sl.length != length)
      return false;
    bool is_eq = true;
    for (int i = 0; i != length; ++i) {
      if (students[i] != sl.students[i])
        return false;
    }
    return true;
  }

  ~StudentList() {
    if (students)
      delete students;
    students = nullptr;
  };
};
