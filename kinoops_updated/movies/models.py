from django.db import models

# Create your models here.


class MovieWebsite(models.Model):
    name = models.CharField(max_length=50 , default='')
    html_name = models.CharField(max_length=50 , default='')

    def __str__(self):
        return self.name


class Genre(models.Model):
    name = models.CharField(max_length=40 , default='')
    html_name = models.CharField(max_length=40 , default='')

    def __str__(self):
        return self.name


class Director(models.Model):
    name = models.CharField(max_length=40 , default='')
    html_name = models.CharField(max_length=40 , default='')

    def __str__(self):
        return self.name


class Category(models.Model):
    name = models.CharField(max_length=40 , default='')
    html_name = models.CharField(max_length=40 , default='')

    def __str__(self):
        return self.name


class Actor(models.Model):
    name = models.CharField(max_length=50 , default='')
    html_name = models.CharField(max_length=40 , default='')

    def __str__(self):
        return self.name


class Country(models.Model):
    name = models.CharField(max_length=100)
    html_name = models.CharField(max_length=40 , default='')

    def __str__(self):
        return self.name


class Link(models.Model):
    website_name = models.ForeignKey(MovieWebsite , default='')
    link = models.CharField(max_length=200 , default='')

    def __str__(self):
        return self.website_name.name + str(self.id)


class Movie(models.Model):
    title = models.CharField(max_length=200)
    overview = models.TextField(max_length=1000, blank=True)
    image = models.ImageField(upload_to='movies', default='images/car1.jpg', blank=True)

    countries = models.ManyToManyField(Country, blank=True)
    genres = models.ManyToManyField(Genre, blank=True)
    actors = models.ManyToManyField(Actor, blank=True)
    categories = models.ManyToManyField(Category, blank=True)
    directors = models.ManyToManyField(Director, blank=True)
    links = models.ManyToManyField(Link, blank=True)

    movie_date = models.DateField(blank=True)
    upload_date = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.title

    class Meta:
        ordering = ('upload_date',)




