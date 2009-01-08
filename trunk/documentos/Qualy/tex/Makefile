all:
	@rm -f ../qualy.pdf
	@pdflatex qualy.tex
	pdflatex qualy.tex
	@mv qualy.pdf ..
	acroread ../qualy.pdf

clean:
	@./.apagar.sh
