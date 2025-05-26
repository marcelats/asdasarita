all:	
	@more COPYRIGHT
	@Ask License
	@Ask License.gnu
	date
	@echo 'Begin making'
	(cd func; Make_all)
	@echo 'Unconditionally make the rest of SimPack3:'
	@echo 'Declarative ...'
	(cd dec; make all)
	@echo 'Multimodel ...'
	(cd multimodel; make all)
	@echo 'Constraint ...'
	(cd constraint; make all)
	@echo 'Spatial ...'
	(cd spatial/gas; make all)
	@echo 'The make has completed,'
	@echo 'now calculate kb of space used by SimPack3...'
	@du -s .
	@echo '(Should be around 13000 kb, depending on compiler & linker)'
	@echo "SimPack3 has been made."
	date

clean:	
	@more COPYRIGHT
	date
	@echo 'Begin cleaning'
	find . -name '*~' -exec rm {} \;
	(cd func; Make_clean)
	(cd dec; make clean)
	(cd multimodel; make clean)
	(cd constraint; make clean)
	(cd spatial/gas; make clean)
	@echo 'Calculating kb of space used by SimPack3...'
	@du -s .
	@echo '(Should be around 4900 kb)'
	@echo "Simpack3 has been cleaned."
	date

