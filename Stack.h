class CStack final
    {
    private:
    double* buffer_;
    size_t size_;
    size_t mem_size_;

    unsigned last_hash;

    bool DeleteBuffer () {delete[] buffer_; return true;};

    void operator = (const CStack&);

    public:
    CStack  (                      );
    CStack  (const CStack& Original);
    ~CStack (                      ) {DeleteBuffer ();}

    const double* Adress       () const {return buffer_;  }
    unsigned      MySize       () const {return size_;    }
    unsigned      My_mem_size_ () const {return mem_size_;}

    bool          ChangeBuffer (double* buffer, bool should_I_delete = true);

    void          Push         (double new_item);
    double        Pop          (               );

    void          Dump         () const;
    unsigned      Hash         () const;

    bool          Checker      () const ;
    };

CStack::CStack () :
    size_ (0),
    buffer_ (new double[1]),
    mem_size_ (1),
    last_hash (0)
    {
    last_hash = Hash ();
    }

CStack::CStack (const CStack& Original) :
    buffer_ (new double[Original.MySize ()]),
    size_ (Original.MySize ()),
    mem_size_ (Original.My_mem_size_ ()),
    last_hash (0)
    {
    std::copy(Original.Adress(), Original.Adress() + size_, buffer_);

    last_hash = Hash ();
    }

bool CStack::ChangeBuffer (double* buffer, bool should_I_delete /*= true*/)
    {
    if (should_I_delete) DeleteBuffer ();
    buffer_ = buffer;

    last_hash = Hash ();

    return true;
    }

void CStack::Push (double new_item)
    {
    if (mem_size_ == size_)
        {
        mem_size_ = mem_size_*2;

        double* new_buffer = new double[mem_size_];

        std::copy(buffer_, buffer_ + mem_size_/2, new_buffer);

        buffer_ = new_buffer;
        }

    size_++;
    buffer_[size_-1] = new_item;

    last_hash = Hash ();
    }

double CStack::Pop ()
    {
    if (size_ == 0)
        {
        std::cout << "You're trying to do bad things! \n";

        return 0.0;
        }

    double resault = buffer_[size_ - 1];

    size_--;

    last_hash = Hash ();

    return resault;
    }

void CStack::Dump () const
    {
    std::cout << "Stack: \n";
    std::cout << "  Size    " << size_ << std::endl;
    std::cout << "  MemSize " << mem_size_ << std::endl;
    std::cout << "  Hash    " << Hash () << std::endl;

    for (unsigned i = 0; i < size_; i++)
        {
        std::cout << "    " << buffer_[i] << std::endl;
        }

    Checker ();
    }

unsigned CStack::Hash ()const
    {
    unsigned resualt = 0;

    resualt += (unsigned)buffer_ + (unsigned)(&size_) + (unsigned)(&mem_size_);
    resualt += 3*size_ + 5*mem_size_;

    for (unsigned i = 0; i < size_; i++)
        {
        resualt += (unsigned)buffer_[i]/7;
        }

    return resualt;
    }

bool CStack::Checker ()const
    {
    if (Hash () != last_hash)
        {
        std::cout << "Oh, my hash changed illegal!";

        return true;
        }

    return false;
    }


