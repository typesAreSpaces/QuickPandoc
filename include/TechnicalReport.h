#ifndef _REPORT_
#define _REPORT_

#include "PandocWriter.h"

class TechnicalReport : public PandocWriter {
  void HeaderSection(std::ostream &)  const;
  void PackageSection(std::ostream &) const;
  void MainSection(std::ostream &)    const;

  public:
  TechnicalReport(std::string const &);
  TechnicalReport(
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
