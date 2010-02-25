all:
	@rm -f ../Dissert.pdf
	@./.apagar.sh
	@pdflatex Dissert.tex
	cp ../../bibliografia.bib .
	@bibtex Dissert
	@pdflatex Dissert.tex
	@bibtex Dissert
	pdflatex Dissert.tex
	@mv Dissert.pdf ..
	acroread ../Dissert.pdf
	@./.apagar.sh
