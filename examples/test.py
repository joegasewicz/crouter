from bindings import CRouter


class HomeHandler:
    pass


routes = [
    ("/", HomeHandler),
]


if __name__ == "__main__":
    router = CRouter()
    router.parse(routes)
