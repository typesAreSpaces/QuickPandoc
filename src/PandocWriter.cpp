#include "PandocWriter.h"

PandocWriter::PandocWriter(std::string const & project_name) :
  PandocWriter(
      project_name, 
      "Author's name", 
      "QuickPandoc sample file"
      ) 
{}

PandocWriter::PandocWriter(
    std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) :
  project_name(project_name), 
  author_name(author_name),
  title(title)
{
  system(("mkdir -p " + project_name).c_str());
  system(("mkdir -p " + project_name + "/figures").c_str());
  BasicMakefile();
}

void PandocWriter::BasicMakefile() const {
  std::ofstream out((project_name + "/Makefile").c_str());

  out << 
    "SRC=$(wildcard *.md)\n"
    "TEX_FILES=$(SRC:.md=.tex)\n"
    "MAIN_MD=main.md\n"
    "MAIN_TEX=$(MAIN_MD:.md=.tex)\n"
    "MAIN_OUTPUT=$(MAIN_MD:.md=.pdf)\n" 

    "%.tex: %.md\n"
    "\tif [ ! $< == main.md ]; then pandoc $< -o $@; fi\n"

    "$(MAIN_OUTPUT): $(TEX_FILES) $(MAIN_MD)\n"
    "\tpandoc $(MAIN_MD) -s -o $(MAIN_TEX)\n"
    "\trubber --pdf $(MAIN_TEX)\n"
    ".PHONY: clean\n"
    "clean:\n"
    "\trubber --clean $(MAIN_TEX)\n"
    "\trm -rf $(TEX_FILES)\n"
    "\trm -rf $(MAIN_OUTPUT)\n"

    "watch:\n"
    "\t@while true; do inotifywait $(SRC); sleep 0.01; make $(MAIN_OUTPUT); done\n"
    << std::endl;
  return;
}

std::string PandocWriter::BasicPandocSectionContent(
    std::string const & file_name,
    std::string const & section_name, 
    std::string const & content
    ) const {
  std::ofstream out((project_name + "/" + file_name + ".md").c_str(), std::ios_base::app);
  out << "# " + section_name + "\n";
  out << content;
  out.close();
  return "\\input{" + file_name + "}\n";
}
