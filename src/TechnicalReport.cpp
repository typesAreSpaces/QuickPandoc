#include "TechnicalReport.h"

TechnicalReport::TechnicalReport(std::string const & project_name) :
  PandocWriter(project_name) 
{
}

TechnicalReport::TechnicalReport(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) : PandocWriter(project_name, author_name, title) 
{
  std::ofstream out((project_name + "/main.md").c_str());
  HeaderSection(out);
  MainSection(out);
  out.close();
}

void TechnicalReport::HeaderSection(std::ostream & out) const {
  out << 
    "---\n"
    "title: " << title << "\n"
    "author: " << author_name << "\n"
    "date: \\today\n"
    "documentclass: IEEEtran\n"
    "abstract: The abstract text goes here.\n"
    "header-includes: | \n";
  PackageSection(out);
  out << 
    "...\n"
    << std::endl;
  return;
}

void TechnicalReport::PackageSection(std::ostream & out) const {
  out << 
    "\t\\usepackage{graphicx}\n"
    "\t\\usepackage[utf8]{inputenc}\n"
    "\t\\usepackage{cite}\n"
    "\t\\usepackage{url}\n"
    "\t\\usepackage[english]{babel}\n"
    "\t\\usepackage{verbatim}\n"
    "\t\\usepackage{etoolbox}\n"
    "\t\\usepackage{float}\n"
    "\t\\usepackage{pdfpages}\n"
    "\t\\usepackage{rotating}\n"
    "\t\\usepackage{tikz}\n"
    "\t\\usetikzlibrary{positioning,fit,arrows.meta,backgrounds}\n"
    "\t\\usepackage{hyperref}\n"
    "\t\\usepackage{algpseudocode}\n"
    "\t\\usepackage{algorithm}\n"
    "\t\\usepackage{ebproof}\n"
    "\t\\usepackage{booktabs}\n"
    "\t\\usepackage{multirow}\n"
    "\t\\usepackage{listing}\n"
    "\t\\usepackage{symbols}\n"
    << std::endl;
  return;
}

void TechnicalReport::MainSection(std::ostream & out) const {
  out << BasicPandocSectionContent(
      "introduction", 
      "Introduction", 
      "TODO: write introduction"
      ) 
    << std::endl;

  out << BasicPandocSectionContent(
      "conclusion", 
      "Conclusion", 
      "TODO: write conclusion"
      ) 
    << std::endl;

  out << 
    "<!--\\bibliographystyle{plain}-->\n"
    "<!--\\bibliography{references}-->\n"
    << std::endl;

  return;
}
