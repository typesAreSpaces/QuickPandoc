#ifndef _HOMEWORK_
#define _HOMEWORK_

#include "PandocWriter.h"

class Homework : public PandocWriter {
  void HeaderSection(std::ostream &)  const;
  void PackageSection(std::ostream &) const;
  void MainSection(std::ostream &)    const;

  std::string const & subject;
  std::string const & due_date;
  std::string const & prof_name;

  public:
  Homework(
      std::string const &, 
      std::string const &, 
      std::string const &, 
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
