## Without `virtual`

```
Person::ctor
Teacher::ctor
Person::ctor
Student::ctor
Student::dtor
Person::dtor
Teacher::dtor
Person::dtor
```

## With `virtual`

```
Person::ctor
Teacher::ctor
Student::ctor
Student::dtor
Teacher::dtor
Person::dtor
```
