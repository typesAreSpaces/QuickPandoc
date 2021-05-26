#include "Homework.h"

Homework::Homework(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title, 
    std::string const & subject,
    std::string const & due_date,
    std::string const & prof_name
    ) : PandocWriter(project_name, author_name, title), 
  subject(subject), due_date(due_date), prof_name(prof_name)
{
  std::ofstream out((project_name + "/main.md").c_str());
  HeaderSection(out);
  MainSection(out);
  out.close();
}

void Homework::HeaderSection(std::ostream & out) const {
  out << 
    "---\n"
    "title: " << title << "\n"
    "author: " << author_name << "\n"
    "date: " << due_date << "\n"
    "documentclass: article\n"
    "header-includes: | \n";
  PackageSection(out);
  out << 
    "...\n"
    << std::endl;
  return;
}

void Homework::PackageSection(std::ostream & out) const {
  out <<
    "\t\\renewcommand{\\maketitle}{}\n"
    "\t\\usepackage{comment}\n"
    "\t\\usepackage[utf8]{inputenc}\n"
    "\t\\usepackage{amsmath}\n"
    "\t\\usepackage{amsfonts}\n"
    "\t\\usepackage{amssymb}\n"
    "\t\\usepackage{titlesec}\n"
    "\t\\usepackage[left=3cm,right=3cm,top=4cm,bottom=4cm]{geometry}\n"
    "\t\\usepackage{fancyhdr}\n"
    "\t\\usepackage{extramarks}\n"
    "\t\\usepackage{symbols}\n"
    "\t\\newcommand{\\Name}{\\textbf{" + author_name + "}}\n"
    "\t\\newcommand{\\Title}{" + title + "}\n"
    "\t\\newcommand{\\Subject}{" + subject + "}\n"
    "\t\\newcommand{\\DueDate}{" + due_date + "}\n"
    "\t\\newcommand{\\Instructor}{" + prof_name + "}\n"
    "\t\\pagestyle{fancy}\n"
    "\t\\lhead{\\Name}\n"
    "\t\\chead{\\Subject\\ -\\ \\Instructor\\ :\\ \\Title}\n"
    "\t\\rhead{\\DueDate}\n"
    "\t\\newenvironment{homeworkProblem}[1][0]{\n"
    "\t\\section{Problem: #1}\n"
    "\t}{\n"
    "\t}\n"
    << std::endl;

  return;
}

void Homework::MainSection(std::ostream & out) const {
  out <<
    "\\begin{homeworkProblem}\n"
    "%%Problem text goes here.\n"
    "%%Solution text goes here.\n"
    "\\end{homeworkProblem}\n"
    << std::endl;

 out << 
   "<!--\\bibliographystyle{plain}-->\n"
   "<!--\\bibliography{references}-->\n"
   << std::endl;

  return;
}
