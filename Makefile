MODULE = fibonacci


.PHONY: run build clean

run: build
	python main.py 12

build: clean
	python -m pip install -e .

clean:
	python -m pip uninstall -y $(MODULE)
	rm -rf \
		build \
		$(MODULE).egg-info \
		$(MODULE)/*.so $(MODULE)/*.c