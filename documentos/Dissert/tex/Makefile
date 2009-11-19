all:
	@rm -f ../Qualy.pdf
	@./.apagar.sh
	@pdflatex Qualy.tex
	cp ../../bibliografia.bib .
	@bibtex Qualy
	@pdflatex Qualy.tex
	bibtex Qualy
	pdflatex Qualy.tex
	@mv Qualy.pdf ..
	acroread ../Qualy.pdf
	@./.apagar.sh
