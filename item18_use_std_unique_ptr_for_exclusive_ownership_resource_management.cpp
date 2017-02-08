//
// Created by marci_000 on 04.02.2017.
//

#include <memory>
#include <utility>
#include <iostream>
#include <string>
#include "item18_use_std_unique_ptr_for_exclusive_ownership_resource_management.h"

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

class Base {
 public:
  virtual ~Base() = default;
};

class Derived1 : public Base {
 public:
  Derived1(std::string s, int i) {}
};

class Derived2 : public Base {
 public:
  Derived2(std::string s, std::string s2) {}
};

enum class BaseType {
  Derived1,
  Derived2
};

template<typename... Ts>
std::unique_ptr<Base> makeBase(BaseType type, Ts&&... args) {
  std::unique_ptr<Base> ptr;
  if (type == BaseType::Derived1)
    ptr.reset(new Derived1(std::forward<Ts>(args)...));
  if (type == BaseType::Derived2)
    ptr.reset(new Derived2(std::forward<Ts>(args)...));
  return ptr;
}

void delBase(Base* pBase) {
//void delBase(void* pBase) {
  std::cout << "delBase\n";
  delete pBase;
}

std::unique_ptr<std::string> GetStringPtr() {
  return std::unique_ptr<std::string>(new std::string("test"));
}

void item18_use_std_unique_ptr_for_exclusive_ownership_resource_management::run() {

  // Does not compile, for obvious reasons, see here for more:
  // http://stackoverflow.com/questions/42077494/factory-function-using-variadic-args-template-and-unique-ptr?noredirect=1#comment71326764_42077494
  //auto d1 = makeBase(BaseType::Derived1, "aa", 1);

  using BasePtr = std::unique_ptr<Base, decltype(&delBase)>;
  BasePtr ptr = BasePtr(new Derived1("test", 0), delBase);

  std::cout << "decltype(delBase) : function type! : " << type_id_with_cvr<decltype(delBase)>().pretty_name() << "\n";
  std::cout << "decltype(&delBase) : pointer to function type! : " << type_id_with_cvr<decltype(&delBase)>().pretty_name() << "\n";

  // Now lets see sizes of unique_ptr

  // Below two has 8 bytes each
  char* pRaw = new char(1);
  std::unique_ptr<char> pSmart = std::unique_ptr<char>(new char(1));
  std::cout << "sizeof(pRaw) = " << sizeof(pRaw) << "\n";
  std::cout << "sizeof(std::unique_ptr<char>) = " << sizeof(pSmart) << "\n";

  auto charDeleter = [](char* pV) { delete pV; };
  std::unique_ptr<char, decltype(charDeleter)> pSmart2 = std::unique_ptr<char, decltype(charDeleter)>(new char(1), charDeleter);
  std::cout << "sizeof(std::unique_ptr<char, decltype(charDeleter)>) = " << sizeof(pSmart2) << "\n";

  // Below doubles size of unique_ptr (16 bytes). This is becase of captures int and probably alignment (??)
//#pragma pack (1) // no effect
  int count = 0;
  auto charDeleter2 = [&](char* pV) { count++; delete pV; };
  std::unique_ptr<char, decltype(charDeleter2)> pSmart3 = std::unique_ptr<char, decltype(charDeleter2)>(new char(1), charDeleter2);
  std::cout << "sizeof(std::unique_ptr<char, decltype(charDeleter2)>) = " << sizeof(pSmart3) << "\n";
//#pragma pack ()

  // Only extra code inside lambda, does not make unique_ptr larger it is still 8 bytes.
  auto charDeleter3 = [](char* pV) { std::cout << "Some test\n"; delete pV; };
  std::unique_ptr<char, decltype(charDeleter3)> pSmart4 = std::unique_ptr<char, decltype(charDeleter3)>(new char(1), charDeleter3);
  std::cout << "sizeof(std::unique_ptr<char, decltype(charDeleter3)>) = " << sizeof(pSmart4) << "\n";

  // Lests see how T[] specialization is doing.
  std::unique_ptr<char[]> ptrArr = std::unique_ptr<char[]>(new char[100]);
  ptrArr[1] = '1';
  ptrArr[2] = '2';
  //pSmart4[1] = '1'; // no T[] pointer, so no operator[] available OK!
  //*ptrArr = '1'; // thats ok, there is no dereference operator for T[] version

  // Now lets convert unique_ptr to shared_ptr - awesome!
  std::unique_ptr<std::string> strPtr(new std::string("test"));
  std::shared_ptr<std::string> strSPtr(std::move(strPtr));

  //
  std::shared_ptr<std::string> sp(GetStringPtr());
}
