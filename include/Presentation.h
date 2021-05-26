#ifndef _PRESENTATION_
#define _PRESENTATION_

#include "PandocWriter.h"

class Presentation : public PandocWriter {
  void RewriteMakefile() const;

  void HeaderSection(std::ostream &)  const;
  void PackageSection(std::ostream &) const;
  void MainSection(std::ostream &)    const;

  std::string BasicPresentationSectionContent(
    std::string const &,
    std::string const &,
    std::string const &) const;

  public:
  Presentation(std::string const &);
  Presentation(
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
