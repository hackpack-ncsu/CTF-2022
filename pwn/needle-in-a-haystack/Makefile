# Change to "ctf2021-${YOUR_CHALLENGE_NAME}"
IMAGE_BASE = ctf2022-needle-in-a-haystack

# Change to the relative path to your challenge's subfolder of the CTF-2021 git repo.
# This is done so that your Docker builds are always tagged with the git subtree hash
# of your latest committed changes in that specific sub folder, as opposed to the entire
# hash of the latest commit across the entire repo.
SRC_SUBTREE = pwn/needle-in-a-haystack

# And leave the rest of this alone...
#------------------------------------

IMAGE_TAG = `git rev-parse --verify --short=0 HEAD:${SRC_SUBTREE}`
IMAGE_NAME = $(IMAGE_BASE):$(IMAGE_TAG)


docker:
	docker build -t $(IMAGE_NAME) .
	docker tag $(IMAGE_NAME) $(IMAGE_BASE):latest

install: docker
	sh xinetd_conf.sh $(IMAGE_TAG) /etc/xinetd.d/${IMAGE_BASE}
	systemctl restart xinetd

test: chal
	echo "$(CURDIR)/chal"
	nc --verbose --exec "$(CURDIR)/chal" --listen

chal: main.c main.h
	gcc -o $@ $< -g -O0 -std=c99

clean:
	rm -rf chal	

