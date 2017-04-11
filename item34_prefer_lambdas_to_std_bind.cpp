//
// Created by marcin on 10.04.17.
//

#include "item34_prefer_lambdas_to_std_bind.h"

#include <boost/type_index.hpp>
#include <functional>
#include <chrono>
#include <iostream>
#include <algorithm>

using boost::typeindex::type_id_with_cvr;
using namespace std::literals;
using namespace std::placeholders;

using Time = std::chrono::steady_clock::time_point;
enum class Sound { Beep, Siren, Whistle };
using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {
  // Use to_time_t to convert steady_clock to ctime
  // http://stackoverflow.com/questions/18361638/converting-steady-clocktime-point-to-time-t
  auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + (t - std::chrono::steady_clock::now()));
  std::string ts = std::ctime(&tt);
  std::replace(ts.begin(), ts.end(), '\n', ' ');
  std::cout << "setAlarm: "
            << ts
            << ", "
            << "sound: " << static_cast<int>(s)
            << ", duration: "
            << std::chrono::duration_cast<std::chrono::seconds>(d).count()
            << "s\n";
}

void setAlarm2(Time t, Sound s, Duration d) {
}
void setAlarm2(Time t, Sound s, Duration d, int vol) {
}

struct X {
  template<typename T>
  void operator()(const T& param) const {
    std::cout << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
  }
};

void item34_prefer_lambdas_to_std_bind::run() {

  std::cout << "1. use lambda to generalize a function call - we want to callsetAlarm with only one parameter.\n";
  auto fn1 = [](Sound s) { setAlarm(std::chrono::steady_clock::now() + 1h, s, 30s); };
  fn1(Sound::Beep);

  std::cout << "2. Now the same with std::bind - lets see how more difficult it will get.\n";
  // Below is actually wrong, as `std::chrono::steady_clock::now() + 1h` is evaluated at the bind object creation, and
  // not when it is created.
  auto fn2 = std::bind(setAlarm, std::chrono::steady_clock::now() + 1h, _1, 30s);
  fn2(Sound::Beep);

  std::cout << "2.1. Solution to above problem with first argument evaluation.\n";
  // We will use std::bind to defer evaluation:
  auto fn3 = std::bind(setAlarm,
                       std::bind(std::plus<>(),
                                 std::bind(std::chrono::steady_clock::now),
                                 1h),
                       _1, 30s);
  fn3(Sound::Beep);

  std::cout << "\n\n3. Using overloads with lambdas and std::bind.\n";

  // This is fine !
  auto fn4 = [](Sound s) { setAlarm2(std::chrono::steady_clock::now() + 1h, s, 30s); };
  fn4(Sound::Beep);

  // Uncomment this overload to see how std::bind fails to choose the correct overload version.
  // If you want to make it compile then you need to cast setAlarm2 to the correct function overload.
  /*
  auto fn5 = std::bind(setAlarm2,
                       std::bind(std::plus<>(),
                                 std::bind(std::chrono::steady_clock::now),
                                 1h),
                       _1, 30s);
  fn5(Sound::Beep);
  */
  using setAlarm23ParamOverloadType = void (*)(Time, Sound, Duration);
  auto fn5 = std::bind(static_cast<setAlarm23ParamOverloadType>(setAlarm2),
                       std::bind(std::plus<>(),
                                 std::bind(std::chrono::steady_clock::now),
                                 1h),
                       _1, 30s);
  fn5(Sound::Beep);

  std::cout << "\n\n4. Binding polymorphic function objects with std::bind.\n";
  X x;
  auto fn6 = std::bind(x, 1);
  fn6();
  std::bind(x, "test")();
  auto fn7 = std::bind(x, std::string("test"));
  fn7();
}
