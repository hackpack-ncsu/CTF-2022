# Change to "ctf2021-${YOUR_CHALLENGE_NAME}"
IMAGE_BASE = ctf2021-xinetd-pty-challenge

# Change to the relative path to your challenge's subfolder of the CTF-2021 git repo.
# This is done so that your Docker builds are always tagged with the git subtree hash
# of your latest committed changes in that specific sub folder, as opposed to the entire
# hash of the latest commit across the entire repo.
SRC_SUBTREE = infra/templates/xinetd-pty-challenge

# For maximal consistency, you can put your flag string in here.
# This example uses it to generate a trivial flag.txt file
# Of course, also feel free to rip this out and just hardcode
# the flag in your source or a text file, depending on your needs.
FLAG = flag{y0u_c@n_put_th3_fl@g_1n_th3_M@k3f1le_t00}

# And leave the rest of this alone...
#------------------------------------

IMAGE_TAG = `git rev-parse --verify --short=0 HEAD:${SRC_SUBTREE}`
IMAGE_NAME = $(IMAGE_BASE):$(IMAGE_TAG)


image:
	echo "$(FLAG)" >./root/flag.txt	
	docker build -t $(IMAGE_NAME) .
	docker tag $(IMAGE_NAME) $(IMAGE_BASE):latest

install: 
	sh xinetd_conf.sh $(IMAGE_TAG) /etc/xinetd.d/${IMAGE_BASE}
	systemctl restart xinetd

clean:
	rm -f ./root/flag.txt

