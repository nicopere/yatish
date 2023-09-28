yatish:
	codeblocks --build --target=Release yatish.cbp
# (yatish.cbp is a kind of makefile)

resourcedir=/usr/local/share/yatish
install:
	mkdir -p $(resourcedir)/fr
	cp fr/yatish.mo $(resourcedir)/fr/
	cp sql/yatish.sqlite sql/yatish.auth $(resourcedir)/
	cp bin/Release/yatish /usr/local/bin/
	cp yatish.desktop /usr/share/applications/
	cp src/yatish.xpm /usr/share/pixmaps/
uninstall:
	rm -rf $(resourcedir)
	rm -f /usr/local/bin/yatish
	rm -f /usr/share/applications/yatish.desktop
	rm -f /usr/share/pixmaps/yatish.xpm

# next 2 targets need HelpBlocks from Anthemion Software
yatish-help:
	helpblocks -w help/yatish.wxh # returns 255 although it's OK
install-help:
	cp help/yatish.htb $(resourcedir)/

clean:
	codeblocks --clean --target=Release yatish.cbp
mrproper:
	svn cleanup --remove-unversioned
