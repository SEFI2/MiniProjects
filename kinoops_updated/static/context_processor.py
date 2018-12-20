
from movies.models import Genre, Country

def add_navbar(request):
    genres = Genre.objects.all()
    countries = Country.objects.all()
    return {
        "genres" : genres,
        "countries" : countries
    }
