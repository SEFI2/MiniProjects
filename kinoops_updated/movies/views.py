from django.shortcuts import render
from .models import Movie
from extraapps.models import CarouselImage


# Create your views here.

def home_page(request):
    movies = Movie.objects.all()[:20]
    carousel = CarouselImage.objects.all()
    return render(request , 'movies/home_page.html' , {"movies":movies , "carousel" : carousel})


def movie_list(request , filter_type, filters):
    if filter_type == 'genre':
        movies = Movie.objects.filter(genres__name__contains=filters)
    elif filter_type == 'category':
        movies = Movie.objects.filter(categories__name__contains=filters)
    elif filter_type == 'country':
        movies = Movie.objects.filter(countries__name__contains=filters)
    else:
        movies = Movie.objects.all()
    return render(request , 'movies/movie_list.html' , {"movies":movies})
