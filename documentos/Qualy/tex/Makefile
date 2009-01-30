all:
	@rm -f ../Qualy.pdf
	@pdflatex Qualy.tex
	cp ../../bibliografia.bib .
	@bibtex Qualy
	@pdflatex Qualy.tex
	pdflatex Qualy.tex
	@mv Qualy.pdf ..
	acroread ../Qualy.pdf
	@./.apagar.sh
