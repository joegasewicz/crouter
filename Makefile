build_cython:
	pipenv run python setup.py build_ext --inplace

clean:
	rm -rf build/ bindings/*.so