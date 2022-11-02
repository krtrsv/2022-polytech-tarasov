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
  Student *_stud;
  std::size_t _size;

  StudentList &_set_score(const char *n, int ns) {
    for (std::size_t i = 0; i < _size; ++i) {
      if (!std::strcmp(_stud[i].name, n)) {
        _stud[i].score = ns;
        return *this;
      }
    }
    return *this;
  }

  StudentList &_remove(const char *n) {
    for (std::size_t i = 0; i < _size; ++i) {
      if (!std::strcmp(_stud[i].name, n)) {
        for (std::size_t x = i; x < _size - 1; ++x)
          _stud[x] = _stud[x + 1];
        Student *tmp =
            (Student *)std::realloc(_stud, (_size - 1) * sizeof(Student));
        if (tmp == NULL && _size > 1)
          exit(EXIT_FAILURE);
        _size--;
        _stud = tmp;
        return *this;
      }
    }
    return *this;
  }

public:
  StudentList() : _size{0} {}

  StudentList(std::initializer_list<Student> list)
      : _stud{new Student[list.size()]}, _size{list.size()} {
    for (std::size_t i = 0; const auto &elem : list) {
      _stud[i] = elem;
      i++;
    }
  }

  StudentList(const StudentList &other) : _size{other._size} {
    delete[] _stud;
    _stud = other._stud;
  }

  ~StudentList() {
    if (_stud) {
      delete[] _stud;
      _stud = nullptr;
    }
  };

public:
  StudentList &operator=(const StudentList &other) {
    if (this == &other)
      return *this;
    _size = other._size;
    _stud = (Student *)std::realloc(_stud, _size * sizeof(Student));
    for (std::size_t i = 0; i != _size; ++i)
      _stud[i] = other._stud[i];
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &out, StudentList &sl) {
    if (sl._size == 0) {
      out << "[]";
      return out;
    }
    out << "[\n";
    for (std::size_t i = 0; i < sl._size; ++i) {
      out << "  " << sl._stud[i];
      if (i + 1 != sl._size)
        out << ", \n";
    }
    out << "\n]";
    return out;
  }

  const bool operator==(const StudentList &sl) const {
    if (sl._size != _size)
      return false;
    for (std::size_t i = 0; i != _size; ++i) {
      if (_stud[i] != sl._stud[i])
        return false;
    }
    return true;
  }

public:
  /// Append `Student` object to students array
  StudentList &append(Student &stud) {
    _size++;
    auto tmp = new Student[_size];
    for (std::size_t i = 0; i < _size - 1; ++i)
      tmp[i] = _stud[i];
    tmp[_size - 1] = stud;
    delete[] _stud;
    _stud = tmp;
    return *this;
  }
  StudentList &append(const char *n, int s) {
    auto stud = Student{n, s};
    return this->append(stud);
  }

  /// Remove first occurance of student in students array
  StudentList &remove(const char *n) { return _remove(n); }
  StudentList &remove(Student &s) { return _remove(s.name); }

  /// Set score of student
  StudentList &set_score(const char *n, int ns) { return _set_score(n, ns); }
  StudentList &set_score(Student &sl, int ns) {
    return _set_score(sl.name, ns);
  }

  /// Get average score of students
  double get_avg_score() const {
    double score_sum = 0;
    for (std::size_t i = 0; i < _size; ++i) {
      score_sum += _stud[i].score;
    }
    return score_sum / _size;
  }

  Student find_student(const char *n) {
    for (std::size_t i = 0; i < _size; ++i) {
      if (!std::strcmp(_stud[i].name, n))
        return _stud[i];
    }
    return Student{};
  }

  /// Get array of students with score >6
  StudentList get_best_students() const {
    StudentList best_students{};
    for (std::size_t i = 0; i < _size; ++i) {
      if (_stud[i].score > 6)
        best_students.append(_stud[i]);
    }
    return best_students;
  }

  /// Get array of students with score <4
  StudentList get_worst_students() const {
    StudentList worst_students{};
    for (std::size_t i = 0; i < _size; ++i) {
      if (_stud[i].score < 4)
        worst_students.append(_stud[i]);
    }
    return worst_students;
  }
};
