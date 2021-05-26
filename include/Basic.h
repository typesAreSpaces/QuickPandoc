#ifndef _BASIC_
#define _BASIC_

#include "PandocWriter.h"

class Basic : public PandocWriter {
  void HeaderSection(std::ostream &)  const;
  void PackageSection(std::ostream &) const;
  void MainSection(std::ostream &)    const;

  public:
  Basic(std::string const &);
  Basic(
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
