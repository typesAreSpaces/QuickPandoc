#ifndef PANDOC_WRITER
#define PANDOC_WRITER

#include <iostream>
#include <fstream>
#include <string>

class PandocWriter {

  void BasicMakefile() const;

  virtual void HeaderSection(std::ostream &)  const = 0;
  virtual void PackageSection(std::ostream &) const = 0;
  virtual void MainSection(std::ostream &)    const = 0;

  protected:
  std::string const & project_name;
  std::string const & author_name;
  std::string const & title;

  std::string BasicPandocSectionContent(
      std::string const &, 
      std::string const &, 
      std::string const &) const ;

  public:
  PandocWriter(std::string const &);
  PandocWriter(
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
