#include "Basic.h"

Basic::Basic(std::string const & project_name) :
  Basic(
      project_name, 
      "Author's name",
      "QuickPandoc sample file"
      ) 
{
}

Basic::Basic(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) : PandocWriter(project_name, author_name, title) 
{
  std::ofstream out((project_name + "/main.md").c_str());
  HeaderSection(out);
  MainSection(out);
  out.close();
}

void Basic::HeaderSection(std::ostream & out) const {
  out << 
    "---\n"
    "title: " << title << "\n"
    "author: " << author_name << "\n"
    "date: \\today\n"
    "documentclass: article\n"
    "abstract: The abstract text goes here.\n"
    "header-includes: | \n";
  PackageSection(out);
  out << 
    "...\n"
    << std::endl;
  return;
}

void Basic::PackageSection(std::ostream & out) const {
  out << 
    "\t\\usepackage{graphicx}\n"
    "\t\\usepackage{comment}\n"
    << std::endl;
  return;
}

void Basic::MainSection(std::ostream & out) const {
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
