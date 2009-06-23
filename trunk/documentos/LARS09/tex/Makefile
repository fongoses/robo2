all:
	@rm -f ../LARS09.pdf
	@./.apagar.sh
	@pdflatex LARS09.tex
	cp ../../bibliografia.bib .
	@bibtex LARS09
	@pdflatex LARS09.tex
	bibtex LARS09
	pdflatex LARS09.tex
	@mv LARS09.pdf ..
	acroread ../LARS09.pdf
	@./.apagar.sh
