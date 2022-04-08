IMAGE_BASE = ctf2022-imported-kimchi
SRC_SUBTREE = web/imported-kimchi
FLAG = flag{y_u_br34k_th3_p1ckl35_1_m4d3}

HOST = 127.0.0.1
PORT = 8101

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
