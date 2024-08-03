#include <iostream>
using namespace std;

typedef int ID;
typedef string Statement;
typedef int Popularity;
enum Dificult { easy, medium, good, hard, impossible };

class Question {
private:
  ID id;
  Statement statement;
  Popularity popularity;
  Dificult dificult;

public:
  Question() : id(0), statement(""), popularity(0), dificult(easy) {}

  Question(ID id, Statement statement, Popularity popularity, Dificult dificult)
      : id(id), statement(statement), popularity(popularity),
        dificult(dificult) {}
  // getset
  ID getId() { return id; }
  void setId(ID id) { this->id = id; }

  Statement getStatement() { return statement; }
  void setStatement(Statement statement) { this->statement = statement; }

  Popularity getPopularity() { return popularity; }
  void setPopularity(Popularity popularity) { this->popularity = popularity; }

  Dificult getDificult() { return dificult; }
  void setDificult(Dificult dificult) { this->dificult = dificult; }
  // basic funcs
  string getDificultLabel() {
    switch (dificult) {
    case easy:
      return "easy";
    case medium:
      return "medium";
    case good:
      return "good";
    case hard:
      return "hard";
    case impossible:
      return "impossible";
    default:
      return "easy";
    }
  }
  void print() {
    cout << getId() << " " << getStatement() << " " << getPopularity() << " "
         << getDificultLabel() << endl;
  }
};

class List {
private:
  Question *questions;
  const int LEN;
  int current_LEN;

public:
  List(int _LEN) : LEN(_LEN) { questions = new Question[LEN]; }

  void create() { current_LEN = 0; }

  void show() {
    cout << "<===== QUESTION LIST =====>" << endl;
    for (int i = 1; i <= current_LEN; ++i)
      questions[i].print();
    cout << "len: " << current_LEN << endl;
  }

  bool isFull() { return current_LEN == LEN; };
  bool isEmpty() { return current_LEN == 0; };
  bool validPos(int i) { return i > 0 && i <= current_LEN; };

  void insert(Question q) {
    if (!isFull())
      questions[++current_LEN] = q;
    else
      cout << "list is full!" << endl;
  }

  Question getQuestionByKey(ID key) {
    int i = 0;
    while (questions[i].getId() != key && i <= current_LEN) {
      ++i;
    }
    if (i <= current_LEN)
      return questions[i];
    else {
      cout << "question not found!" << endl;
      return questions[0];
    }
  }

  Question getQuestionByPos(int i) {
    if (i <= current_LEN || !isEmpty())
      return questions[i + 1];
    else {
      cout << "question not found!" << endl;
      return questions[0];
    }
  }

  int getQuestionPosByKey(ID key) {
    sort();
    int i = 1, j = current_LEN;
    while (i <= j) {
      int mid = (i + j) / 2;
      if (questions[mid].getId() == key)
        return mid;
      else if (key < questions[mid].getId())
        j = mid - 1;
      else
        i = mid + 1;
    }
    return -1;
  }

  void remove(ID key) {
    int pos = getQuestionPosByKey(key);
    if (validPos(pos) && !isEmpty()) {
      for (int i = pos; i < current_LEN; ++i) {
        questions[i] = questions[i + 1];
      }
      --current_LEN;
    } else
      cout << "invalid pos or list is empty!" << endl;
  }

  void sort() {
    int i, j;
    Question temp;
    for (i = current_LEN; i > 0; --i) {
      for (j = 1; j <= i - 1; ++j) {
        if (questions[j].getId() > questions[j + 1].getId()) {
          temp = questions[j];
          questions[j] = questions[j + 1];
          questions[j + 1] = temp;
        }
      }
    }
  }

  int min() {
    if (!isEmpty()) {
      sort();
      return 0;
    } else
      return -1;
  }

  int max() {
    if (!isEmpty()) {
      sort();
      return current_LEN - 1;
    } else
      return -1;
  }

  Question sucessor(int i) {
    if (!isEmpty() && !isFull() && validPos(i) && validPos(i + 1)) {
      return questions[i + 1];
    } else
      return questions[i];
  }

  Question predecessor(int i) {
    if (!isEmpty() && validPos(i) && validPos(i - 1)) {
      return questions[i - 1];
    } else
      return questions[i];
  }

  List getListByDificult(Dificult d) {
    List *l = new List(current_LEN);
    for (int i = 1; i <= current_LEN; ++i) {
      if (questions[i].getDificult() == d) {
        l->insert(questions[i]);
      }
    }
    return *l;
  }
};

int main() {
  const int LEN = 10;
  List *l = new List(LEN);
  l->create();
  Question q2 = Question(20, "matar idosas", 2, easy);
  Question q6 = Question(9, "fazer macumba", 69, good);
  Question q5 = Question(5, "cpi lava toga", 10, medium);
  Question q3 = Question(13, "passar pano", 2, easy);
  Question q4 = Question(44, "votar no 22", 100, easy);
  Question q = Question(1, "fazer o L", 2, hard);
  l->insert(q2);
  l->insert(q3);
  l->insert(q5);
  l->insert(q6);
  l->insert(q4);
  l->insert(q);
  l->show();
  l->sort();
  cout << "sorting...." << endl;
  l->show();
  // ID key = 13;
  // Question myq = l->getQuestionByKey(key);
  // myq.print();

  // int index = 0;
  // Question myaq = l->getQuestionByPos(index);
  // myaq.print();

  // l->remove(key);
  // l->show();

  // int minKeyIndex = l->min();
  // int maxKeyIndex = l->max();
  // Question minQuest = l->getQuestionByPos(minKeyIndex);
  // Question maxQuest = l->getQuestionByPos(maxKeyIndex);
  // cout << "max key: ";
  // maxQuest.print();
  // cout << "min key: ";
  // minQuest.print();
  // l->show();

  // Question qsuc = l->sucessor(4);
  // Question qpred = l->predecessor(2);
  // qsuc.print();
  // qpred.print();

  // Dificult d = easy;
  // List easyList = l->getListByDificult(d);
  // easyList.show();

  // l->show();

  // int myQuesPos = l->getQuestionPosByKey(20);
  // cout << myQuesPos << endl;
  // ;
  // Question myQues = l->getQuestionByPos(myQuesPos);
  // myQues.print();

  delete l;
  l = nullptr;
  return 0;
}