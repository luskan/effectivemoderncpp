//
// Created by marci_000 on 27.04.2017.
//

#include "item40_use_std_atomic_for_concurrency_volatile_for_special_memory.h"

#include <atomic>
#include <iostream>

void item40_use_std_atomic_for_concurrency_volatile_for_special_memory::run() {

  std::atomic<int> ai(0);
  ai = 10;  // this assignment might be optimized away
  ai = 20;
  std::cout << ai << "\n";

  volatile int vc(0);
  vc = 10;  // compiler cannot optimize away this assignment,
            // standard only specifies that volatile be in signal handler, setjmp, MMIO. Specific implementation
            // details are left for the compiler.
            //
            // from msdn for : "volatile (C++)"
            // - those two assignments should not be reordered as processors does not reorder non cachable memory accesses.
            // - if /volatile:iso is specified then vc is cannot be used for intra-thread communication, it can be used only for hardware accesses
            // - if /volatile:ms is specified then vs can be used for intra-thread communication, it gives similar guarantees to std::atomic<>
            //
            // For longer discussion : http://stackoverflow.com/questions/26307071/does-the-c-volatile-keyword-introduce-a-memory-fence
  vc = 20;

}
