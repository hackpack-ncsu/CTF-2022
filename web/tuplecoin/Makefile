IMAGE_BASE = ctf2022-tuplecoin
SRC_SUBTREE = web/tuplecoin
FLAG = flag{th3r3_r_2_k1nds_0f_crypt0_n_7h3_w0r1d___th15_15nt_1_0f_th3m}

# public service endpoint to bind to
HOST = 127.0.0.1
PORT = 8100

# Docker image tagging
IMAGE_TAG = `git rev-parse --verify --short=0 HEAD:${SRC_SUBTREE}`
IMAGE_NAME = $(IMAGE_BASE):$(IMAGE_TAG)

# Makefile targets
#-------------------------------


# build the docker image
docker:
	echo "$(FLAG)" >flag.txt
	tar czf code.tar.gz server/main.py server/requirements.txt
	docker build --network=host -t $(IMAGE_NAME) .
	docker tag $(IMAGE_NAME) $(IMAGE_BASE):latest
	rm -f code.tar.gz
	rm -f flag.txt

# run the current image as a persistent service
install:
	docker rm --force $(IMAGE_BASE)
	docker run -d --name=$(IMAGE_BASE) --restart=always -p $(HOST):$(PORT):80  $(IMAGE_NAME)