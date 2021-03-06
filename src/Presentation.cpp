#include "Presentation.h"

Presentation::Presentation(std::string const & project_name) :
  PandocWriter(project_name) 
{
}

Presentation::Presentation(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) : PandocWriter(project_name, author_name, title) 
{
  RewriteMakefile();
  GenerateScript();
  std::ofstream out((project_name + "/main.md").c_str());
  HeaderSection(out);
  MainSection(out);
  out.close();
}

void Presentation::RewriteMakefile() const {
  std::ofstream out((project_name + "/Makefile").c_str());

  out << 
    "SRC=$(wildcard *.md)\n"
    "TEX_FILES=$(SRC:.md=.tex)\n"
    "MAIN_MD=main.md\n"
    "MAIN_TEX=$(MAIN_MD:.md=.tex)\n"
    "MAIN_OUTPUT=$(MAIN_MD:.md=.pdf)\n" 

    "$(MAIN_OUTPUT): $(SRC)\n"
    "\tpandoc --filter ./scripts/includes.hs -t beamer $(MAIN_MD) -s -o $(MAIN_TEX)\n"
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

void Presentation::GenerateScript() const {
  system(("mkdir -p " + project_name + "/scripts").c_str());
  std::ofstream out((project_name + "/scripts/includes.hs").c_str());
  out << 
    "#!/usr/bin/env runhaskell\n"
    "\n"
    "import Text.Pandoc\n"
    "import qualified Text.Pandoc.JSON as TPJ\n"
    "import qualified Data.Text.IO as TIO\n"
    "import qualified Data.Text as T\n"
    "\n"
    "main :: IO ()\n"
    "main = TPJ.toJSONFilter doInclude\n"
    "\n"
    "doInclude :: [TPJ.Block] -> IO [TPJ.Block]\n"
    "doInclude (x : xs) =\n"
    "  do\n"
    "    extraction <- extractFromInclude x\n"
    "    (extraction ++) <$> doInclude xs\n"
    "doInclude [] = return []\n"
    "\n"
    "extractFromInclude :: TPJ.Block -> IO [TPJ.Block]\n"
    "extractFromInclude cb@(TPJ.CodeBlock (id, classes, namevals) contents) =\n"
    "  case lookup (T.pack \"include\") namevals of\n"
    "    Just f ->\n"
    "      do\n"
    "        content <- TIO.readFile (T.unpack f)\n"
    "        result <- runIO $ do\n"
    "          readMarkdown def content\n"
    "        includeTmp <- handleError result\n"
    "        extractBlocks includeTmp\n"
    "    Nothing -> return [cb]\n"
    "extractFromInclude x = return [x]\n"
    "\n"
    "extractBlocks :: Pandoc -> IO [TPJ.Block]\n"
    "extractBlocks (Pandoc a x) = return x\n"
    << std::endl;
  system(("chmod +x "+ project_name + "/scripts/includes.hs").c_str());

}

void Presentation::HeaderSection(std::ostream & out) const {
  out << 
    "---\n"
    "title: " << title << "\n"
    "author: " << author_name << "\n"
    "date: \\today\n"
    "documentclass: beamer\n"
    "header-includes: | \n";
  PackageSection(out);
  out << 
    "...\n"
    << std::endl;

  return;
}

void Presentation::PackageSection(std::ostream & out) const {
  out << 
    "\t\\usepackage{comment}\n"
    "\t\\usepackage{beamerthemeshadow}\n"
    "\t\\usepackage[utf8]{inputenc}\n"
    "\t\\usepackage[english]{babel}\n"
    "\t\\usepackage{verbatim}\n"
    "\t\\usepackage{etoolbox}\n"
    "\t\\usepackage{float}\n"
    "\t\\usepackage{amsthm}\n"
    "\t\\usepackage{amsmath}\n"
    "\t\\usepackage{amsfonts}\n"
    "\t\\usepackage{amssymb}\n"
    "\t\\usepackage{pdfpages}\n"
    "\t\\usepackage{graphicx}\n"
    "\t\\usepackage{rotating}\n"
    "\t\\usepackage{tikz}\n"
    "\t\\usetikzlibrary{positioning,fit,arrows.meta,backgrounds}\n"
    "\t\\usepackage{hyperref}\n"
    "\t\\usepackage{listings}\n"
    "\t\\usepackage{algpseudocode}\n"
    "\t\\usepackage{algorithm}\n"
    "\t\\usepackage{ebproof}\n"
    "\t\\usepackage{booktabs}\n"
    "\t\\usepackage{multirow}\n"
    "\t\\usepackage{listing}\n"
    "\t\\usepackage{xcolor}\n"
    "\t\\usepackage{mathtools}\n"
    "\t\\usepackage{fancyvrb}\n"
    "\t\\definecolor{unmwhite1}{rgb}{0.94,0.93,0.94}\n"
    "\t\\definecolor{unmgray1}{rgb}{0.44,0.4,0.42}\n"
    "\t\\definecolor{unmgray2}{rgb}{0.54,0.48,0.5}\n"
    "\t\\definecolor{unmgray3}{rgb}{0.59,0.6,0.6}\n"
    "\t\\definecolor{unmgray4}{rgb}{0.74,0.68,0.69}\n"
    "\t\\definecolor{unmgray5}{rgb}{0.75,0.76,0.76}\n"
    "\t\\definecolor{unmred1}{rgb}{0.73,0.14,0.21}\n"
    "\t\\definecolor{unmred2}{rgb}{0.8,0.61,0.62}\n"
    "\t\\definecolor{unmred3}{rgb}{0.79,0.29,0.39}\n"
    "\t\\definecolor{unmred4}{rgb}{0.92,0.75,0.76}\n"
    "\t\\setbeamercolor{structure}{bg=unmgray1,fg=unmred2}\n"
    "\t\\setbeamercolor{palette primary}{bg=unmred1, fg=unmwhite1}\n"
    "\t\\setbeamercolor{palette secondary}{bg=unmgray1, fg=unmgray1}\n"
    "\t\\setbeamercolor{palette tertiary}{bg=unmred2, fg=unmgray1}\n"
    "\t\\setbeamercolor{palette quaternary}{bg=unmred3, fg=unmwhite1}\n"
    "\t\\setbeamercolor{section in toc}{fg=black,bg=white}\n"
    "\t\\setbeamercolor{alerted text}{use=structure,fg=structure.fg!50!black!80!black}\n"
    "\t\\setbeamercolor{titlelike}{parent=palette primary,fg=structure.fg!50!black}\n"
    "\t\\setbeamercolor{frametitle}{bg=unmred1!10!unmwhite1,fg=unmgray1}\n"
    << std::endl;
  return;
}

void Presentation::MainSection(std::ostream & out) const {

  out << BasicPresentationSectionContent(
      "introduction", 
      "Introduction", 
      "TODO: write introduction"
      ) 
    << std::endl;

  out << BasicPresentationSectionContent(
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

std::string Presentation::BasicPresentationSectionContent(
    std::string const & file_name,
    std::string const & section_name, 
    std::string const & content
    ) const {
  std::ofstream out((project_name + "/" + file_name + ".md").c_str(), std::ios_base::app);
  out << "# " + section_name + "\n";
  out << content;
  out.close();
  return "~~~{include=\"" + file_name + ".md\"}\n~~~";
}
