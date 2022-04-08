IMAGE_BASE = ctf2022-imported-kimchi-2
SRC_SUBTREE = web/imported-kimchi-2
FLAG = flag{4nd_h3r3_1_w45_th1nk1ng_v1n3g4r_w45_s4n1t4ry} 
HOST = 0.0.0.0
PORT = 8102

IMAGE_TAG = `git rev-parse --verify --short=0 HEAD:${SRC_SUBTREE}`
IMAGE_NAME = ${IMAGE_BASE}:${IMAGE_TAG}

docker:
	echo "$(FLAG)" > flag.txt
	docker build --network=host -t ${IMAGE_NAME} .
	docker tag ${IMAGE_NAME} ${IMAGE_BASE}:latest
	rm -f flag.txt

install:
	docker rm --force ${IMAGE_BASE}
	docker run -d --name=${IMAGE_BASE} --restart=always -p ${HOST}:${PORT}:5000 ${IMAGE_NAME}
