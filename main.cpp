#include <support/hostname.h>
#include <iostream>

int main() {
  std::cout << "WPIUtil says your hostname is: " << wpi::GetHostname() << std::endl;
  return 0;
}
