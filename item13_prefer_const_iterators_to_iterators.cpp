//
// Created by marci_000 on 19.01.2017.
//

#include <experimental/optional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <boost/type_index.hpp>
#include <deque>
#include "item13_prefer_const_iterators_to_iterators.h"

using boost::typeindex::type_id_with_cvr;

template<typename Container, typename V>
void insert_after(Container& c, V&& value, V&& value_new)  {
  std::cout << "value: "<< type_id_with_cvr<decltype(value)>().pretty_name();
  std::cout << ", value_new: " << type_id_with_cvr<decltype(value_new)>().pretty_name() << "\n";
  auto pos = std::find(std::cbegin(c), std::cend(c), value);
  c.insert(pos, value_new);
}


// This is a test code to find out why gcc defines two versions of std::begin
// http://stackoverflow.com/questions/41795636/implementation-of-stdbegin-in-gcc-stl-why-two-overloads
namespace test_range{

template<typename _Container>
inline auto
begin2(_Container& __cont) -> decltype(__cont.begin())
{
  std::cout << "1: " << type_id_with_cvr<decltype(__cont.begin())>().pretty_name() << "\n";
  return __cont.begin(); }

/**
 *  @brief  Return an iterator pointing to the first element of
 *          the const container.
 *  @param  __cont  Container.
 */
 /*
template<typename _Container>
inline auto
begin2(const _Container& __cont) -> decltype(__cont.begin())
{
  std::cout << "2: " <<type_id_with_cvr<decltype(__cont.begin())>().pretty_name() << "\n";
  return __cont.begin(); }
*/
void run() {
  std::vector<int> ai;
  const std::vector<int>& cai=ai;
  begin2(ai);
  begin2(cai);

  // in output when both begin2 are defined
  //1: __gnu_cxx::__normal_iterator<int*, std::vector<int, std::allocator<int> > >
  //2: __gnu_cxx::__normal_iterator<int const*, std::vector<int, std::allocator<int> > >

   // in output when only first begin2 is defined:
   //1: __gnu_cxx::__normal_iterator<int*, std::vector<int, std::allocator<int> > >
   //1: __gnu_cxx::__normal_iterator<int const*, std::vector<int, std::allocator<int> > >
}

}

void item13_prefer_const_iterators_to_iterators::run() {

  // C++98 like use of const_iterator access to vector:
  std::vector<int> data;
  typedef std::vector<int>::iterator data_itr;
  typedef std::vector<int>::const_iterator data_citr;

  data_citr citr = std::find(static_cast<data_citr>(data.begin()), static_cast<data_citr>(data.end()), 123);
  data.insert(static_cast<data_citr>(citr), 123); // this cast is actually needed when used c++98 compiler only.

  std::vector<int> ai = {1,2,3,4,5};
  insert_after(ai, 4, 9);
  int v1=4,v2=9;
  insert_after(ai, v1, v2);
  const int cv1=4, cv2=9;
  insert_after(ai, cv1, cv2);
  std::ostream_iterator<int> out_it(std::cout, ",");
  std::copy(std::begin(ai), std::end(ai), out_it);
  std::cout << "\n";

  //
  test_range::run();
}
