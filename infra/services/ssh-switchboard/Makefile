IMAGE_BASE = ssh-switchboard
IMAGE_TAG = `git rev-parse --verify --short=0 HEAD`
IMAGE_NAME = $(IMAGE_BASE):$(IMAGE_TAG)


image:
	docker build -t $(IMAGE_NAME) .
	docker tag $(IMAGE_NAME) $(IMAGE_BASE):latest

install:
	mkdir -p /etc/ssh-switchboard
	cp global.conf /etc/ssh-switchboard/global.conf
	mkdir -p /etc/ssh-switchboard/conf.d

	docker inspect $(IMAGE_BASE) >/dev/null 2>&1 && (docker kill $(IMAGE_BASE); docker rm $(IMAGE_BASE)) || true
	docker run -d --name $(IMAGE_BASE) \
		--privileged \
                --restart always \
		--net=host \
		-v /var/run/docker.sock:/var/run/docker.sock \
		-v /etc/ssh-switchboard:/etc/ssh-switchboard:ro \
		$(IMAGE_NAME)

