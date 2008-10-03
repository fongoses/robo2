BACKUPDIR= ~/Backups
SOURCEDIR=source

all: safebak 
	cd $(SOURCEDIR); make

safebak:
	-rar u $(BACKUPDIR)/"safe-robo-`date '+%F-%R'`.bak.rar" $(SOURCEDIR)/ *.c* *.h *.txt

bak: clean
	svn commit
	-rm $(BACKUPDIR)/safe-robo*
	-rar u $(BACKUPDIR)/"robo-`date '+%F'`.bak.rar" *
	scp $(BACKUPDIR)/"robo-`date '+%F'`.bak.rar" tabajara.icmc.usp.br:~/projeto/bak
	
clean:
	cd $(SOURCEDIR); make clean

gprof: 
	cd $(SOURCEDIR); make gprof
