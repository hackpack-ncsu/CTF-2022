IMAGE_BASE = ctf2022-first-arm

SRC_SUBTREE = pwn/first-arm

FLAG = flag{l00k_my_4rm_15_fully_func710n4l}

IMAGE_TAG = `git rev-parse --verify --short=0 HEAD:${SRC_SUBTREE}`
IMAGE_NAME = $(IMAGE_BASE):$(IMAGE_TAG)

docker:
	docker buildx build --platform linux/amd64 -t $(IMAGE_NAME) .
	docker tag $(IMAGE_NAME) $(IMAGE_BASE):latest

install: 
	sh xinetd_conf.sh $(IMAGE_TAG) /etc/xinetd.d/${IMAGE_BASE}
	systemctl restart xinetd

test: chal
	echo "$(CURDIR)/chal"
	ncat --verbose --exec "$(CURDIR)/chal" --listen

chal: chal.c
	aarch64-linux-gnu-gcc -o $@ "-DFLAG_STRING=\"$(FLAG)\"" $^ -fno-stack-protector -z execstack -no-pie

clean:
	rm -rf chal	