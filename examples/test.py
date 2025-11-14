from bindings import CRouter


class HomeHandler:

    def get(self, req, resp):
        return {}


routes = [
    ("/noah", HomeHandler),
]


if __name__ == "__main__":
    router = CRouter()
    router.parse(routes)
