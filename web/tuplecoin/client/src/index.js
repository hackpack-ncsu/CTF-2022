import m from "mithril";


/*
<header class="mb-auto">
    <div>
      <h3 class="float-md-start mb-0">Cover</h3>
      <nav class="nav nav-masthead justify-content-center float-md-end">
        <a class="nav-link active" aria-current="page" href="#">Home</a>
        <a class="nav-link" href="#">Features</a>
        <a class="nav-link" href="#">Contact</a>
      </nav>
    </div>
  </header>
*/
const HeaderBar = {
    pageLinks: [
        {href: "/home", text: "Home"},
        {href: "/accounts", text: "Accounts"},
        {href: "/transfers", text: "Transfer"},
        {href: "/bugs", text: "Bug Bounty"},
    ],
    view: function(vnode) {
        const activeLink = vnode.attrs.page || HeaderBar.pageLinks[0].href;

        return m("header.mb-auto", m("div", [
            m("h3.float-md-start.mb-0", "TupleCoin.app"),
            m("nav.nav.nav-masthead.justify-content-center.float-md-end",
                HeaderBar.pageLinks.map((link) => {
                    const active = link.href == activeLink;
                    return m(m.route.Link, {
                        href: link.href,
                        class: "nav-link" + (active ? " active" : ""),
                        ["aria-current"]: active ? "page" : undefined,
                    }, link.text);
                }).concat(m("a.nav-link", {href: "/docs"}, m.trust("&nbsp;"))),
            ),
        ]));
    },
};

/*
<footer class="mt-auto text-white-50">
            <p>Cover template for <a href="https://getbootstrap.com/" class="text-white">Bootstrap</a>, by <a
                    href="https://twitter.com/mdo" class="text-white">@mdo</a>.</p>
        </footer>
*/
const FooterBar = {
    view: function(vnode) {
        return m("footer.mt-auto.text-white-50", [
            m("p", [
                "Cover template for ",
                m("a.text-white", {href: "https://getbootstrap.com/"}, "Bootstrap"),
                ", by ",
                m("a.text-white", {href: "https://twitter.com/mdo"}, "@mdo"),
                ".",
            ])
        ]);
    },
}

/*
  <main class="px-3">
    <h1>Cover your page.</h1>
    <p class="lead">Cover is a one-page template for building simple and beautiful home pages. Download, edit the text, and add your own fullscreen background photo to make it your own.</p>
    <p class="lead">
      <a href="#" class="btn btn-lg btn-secondary fw-bold border-white bg-white">Learn more</a>
    </p>
  </main>
*/
const HomePage = {
    view: function(vnode) {
        return m.fragment([
            m(HeaderBar, {page: "/home"}),
            m("main.px-3", [
                m("h1", "Introducing TupleCoin"),
                m("p.lead", [
                    "The future of ",
                    m("abbr", {title: "Deminted Finance"}, "DeFi"),
                    " you expect tomorrow..."
                ]),
                m("p.lead", [
                    "...available ",
                    m("em", "yesterday!"),
                ]),
                m("p", "Have you always wanted to H0DL some cryptocurrency, but felt overwhelmed by all the options?"),
                m("p", "So did, and was, I!"),
                m("p", [
                    "My solution was as simple as it was brilliant: my own compound cryptocurrency, the ",
                    m("em", "tuple coin"),
                    " (TuCo)!  Coincidently, that makes it actually ",
                    m("em", "named after me"),
                    ", Tuco Benedicto Pacifico Juan Maria Ramirez, Jr.!"
                ]),
                m("p", [
                    "Now ",
                    m("em", "you"),
                    " can do the same!",
                ]),
                m("p", "(Umm, I mean you can buy my TuCos, not you can make your own cryptocurrency.  I mean, you can of course, but that won't make me rich so I don't recommend you do that, OK?)"),
                m(m.route.Link, {
                    href: "/accounts",
                    class: "btn btn-1g btn-secondary fw-bold border-white bg-white"
                }, "Get Yours!"),

            ]),
            m(FooterBar),
        ]);
    }
}

const Account = {
    storageKey: "__tuco_accounts__",
    list: [],
    loadList: function() {
        const rawAccounts = window.localStorage.getItem(Account.storageKey);
        if (rawAccounts) {
            Account.list = JSON.parse(rawAccounts);
        }
        return Promise.resolve();
    },
    saveList: function() {
        window.localStorage.setItem(Account.storageKey, JSON.stringify(Account.list));
        return Promise.resolve();
    },
    claim: function(accountNum) {
        return m.request({
            method: "POST",
            url: "/api/account/claim",
            withCredentials: true,
            params: { acct_num: accountNum },
        }).then((acct) => {
            Account.list.push(acct);
            Account.saveList();
        }).catch((err) => {
            console.log(err);
        })
    }

};


const AccountsPage = {
    currentNum: 0,
    oninit: Account.loadList,
    view: function(vnode) {
        return m.fragment([
            m(HeaderBar, {page: "/accounts"}),
            m("main.px-3", [
                m("h1", "Claim Your Account #s"),
                m("p.lead", [
                    "Claim them right now!"
                ]),
                m("p", [
                    "The awesome part about TuCo is that you can ",
                    m("em", "pick your own account number"),
                    "!  Say, the first 9 digits of π!"
                ]),
                m("p", "(Actually, you can't claim that account number, as it belongs to me, Tuco!  But you can claim any others you want...)"),
                m("p", "Claim a FREE account today, and we'll give you π free TuCos just to get started!"),
                m("ul.list-group", [
                    m("li.list-group-item", m("form", {
                        onsubmit: (e) => {
                            e.preventDefault();
                            if (vnode.state.currentNum) {
                                Account.claim(vnode.state.currentNum);
                            }
                        }
                    }, [
                        m("label", "Acct. Num"),
                        m("input[type=number][placeholder=Acct. Num]", {
                            oninput: (e) => {
                                vnode.state.currentNum = parseInt(e.target.value);
                            }
                        }),
                        m("input[type=submit][value=Go!].btn-primary")
                    ])),
                ].concat(...Account.list.map((acct) => {
                    return m("li.list-group-item", `#${acct.balance.acct_num} (${acct.balance.num_tuco.toPrecision(6)} TuCo)`);
                })))
            ]),
            m(FooterBar),
        ]);
    }
}

const TransfersPage = {
    fromAccount: 0,
    toAccount: 0,
    xferAmount: 0,
    
    alerts: [],
    alertId: 0,
    showAlert: function(msg, style) {
        this.alerts.push({key: ++this.alertId, msg: msg, style: style});
        m.redraw();
    },
    hideAlert: function(key) {
        const i = this.alerts.findIndex(a => a.key === key);
        if (i >= 0) {
            this.alerts.splice(i, 1);
        }
    },

    oninit: Account.loadList,
    view: function(vnode) {
        return m.fragment([
            m(HeaderBar, {page: "/transfers"}),
            m("main.px-3", [
                m("h1", "Transfer TupleCoins!"),
                m("p.lead", [
                    "Because TupleCoins are for SPENDING!"
                ]),
                m("p", "There's only one reason to have money, crypto or otherwise: to SPEND it!  Use our form to transfer your TuCo to deserving accounts!"),
                m("p", "(Note: we're still trying to figure out how this whole quote-block-chain-un-quote thing works, so don't be surprised if your account balances don't update right away.  Or ever, actually.  But actually, that's why TuCo is soo cool!  You can pay your bills and keep your money at the same time!!)"),
                m.fragment(vnode.state.alerts.map((a) => m("div", [
                    m("div[role=alert].alert.alert-dismissable.text-start", {class: a.style, key: a.key}, [
                        a.msg,
                        m("button[type=button][data-bs-dismiss=alert][aria-label=Close].btn-close", {
                            onclick: (e) => {
                                vnode.state.hideAlert(a.key);
                            }
                        }),
                    ])
                ]))),
                m("form.text-start", {
                    onsubmit: (e) => {
                        e.preventDefault();
                        if (!vnode.state.fromAccount) {
                            vnode.state.showAlert("Hey, you need an account first!", "alert-warning");
                        } else if (!vnode.state.toAccount) {
                            vnode.state.showAlert("Hey, you need to say who's getting the TuCos!", "alert-warning");
                        } else if (!vnode.state.xferAmount) {
                            vnode.state.showAlert("Hey, you need to say how many TuCos you're sending!", "alert-warning");
                        } else {
                            m.request({
                                method: "POST",
                                url: "/api/transaction/certify",
                                body: {
                                    from_acct: vnode.state.fromAccount,
                                    to_acct: vnode.state.toAccount,
                                    num_tuco: vnode.state.xferAmount,
                                },
                                withCredentials: true,
                            }).then((certifiedTransaction) => {
                                console.log("certified the transaction...");
                                console.log(certifiedTransaction);

                                return m.request({
                                    method: "POST",
                                    url: "/api/transaction/commit",
                                    body: certifiedTransaction,
                                    withCredentials: true,
                                });
                            }).then((commitResult) => {
                                if (commitResult === "OK") {
                                    vnode.state.showAlert("Hey, your transaction is approved!", "alert-primary");
                                } else {
                                    vnode.state.showAlert(commitResult, "alert-danger");
                                }
                            }).catch((err) => {
                                console.log(err);
                            })
                        }
                    }
                }, [
                    m(".mb-3.mt-3", [
                        m("label[for=fromAcct].form-label", "From Account"),
                        m("select[id=fromAcct].form-control", {
                            oninit: () => {
                                vnode.state.fromAccount = (Account.list.length > 0) ? Account.list[0].balance.acct_num : 0;
                                console.log(Account.list, vnode.state.fromAccount);
                            },
                            oninput: (e) => {
                                vnode.state.fromAccount = parseInt(e.target.value);
                            }
                        }, Account.list.map((a) => m("option", {key: a.balance.acct_num, value: a.balance.acct_num}, `#${a.balance.acct_num} (${a.balance.num_tuco.toPrecision(6)} TuCo)`))),
                    ]),
                    m(".mb-3", [
                        m("label[for=toAcct].form-label", "To Account Number"),
                        m("input[id=toAcct][type=number][placeholder=Acct. Num].form-control", {
                            oninput: (e) => {
                                vnode.state.toAccount = parseInt(e.target.value);
                            }
                        }),
                    ]),
                    m(".mb-3", [
                        m("label[for=howMuch].form-label", "How Much"),
                        m("input[id=howMuch][type=number][placeholder=TuCo Amount][step=0.000001].form-control", {
                            oninput: (e) => {
                                vnode.state.xferAmount = parseFloat(e.target.value);
                            }
                        }),
                    ]),
                    m(".mb-3", [
                        m("input[type=submit][value=Go!].btn-primary"),
                    ]),
                ]),
            ]),
            m(FooterBar),
        ]);
    }
}

const BugBountyPage = {
    tucoMemes: [
        {href: "tuco1.jpg", blurb: "He fights as savagely as he eats chicken.  Once glance at his soiled napkin and his enemies run screaming."},
        {href: "tuco2.jpg", blurb: "He never found a sack of gold, or crypto, that wasn't worth almost dying for until he thought better of it."},
        {href: "tuco3.jpg", blurb: "He always packs heat, even in the bathtub."},
    ],
    view: function(vnode) {
        const pickedMeme = vnode.state.tucoMemes[(Math.random() * vnode.state.tucoMemes.length) | 0];
        return m.fragment([
            m(HeaderBar, {page: "/bugs"}),
            m("main.px-3", [
                m("h1", "Bug Bounty"),
                m("p.lead", "Can you steal Tuco's TuCos?  If you can, we have a prize for you!!"),
                m("p.text-start", "Things you should know about Tuco before you begin:"),
                m("ul.text-start", [
                    m("li", "His account number is 314159265, and you can't have it."),
                    m("li", [
                        "He absolutely ",
                        m("em", "hates"),
                        " robots, especially ones from Silicon Valley.",
                    ]),
                    m("li", pickedMeme.blurb),
                ]),
                m("img", {src: pickedMeme.href}),
            ]),
            m(FooterBar),
        ]);
    }
}

m.route(document.getElementById("stuffgoeshere"), "/home", {
    "/home": HomePage,
    "/accounts": AccountsPage,
    "/transfers": TransfersPage,
    "/bugs": BugBountyPage,
});