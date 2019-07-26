#include <iostream>
#include <string>
#include <vector>
#include <functional>

class JobPost
{
public:
	JobPost(const std::string &Title)
		: Title{ Title }
	{
	}

	const std::string GetTitle() const noexcept
	{
		return Title;
	}

private:
	std::string Title;
};

class IObserver
{
public:
	virtual void OnJobPosted(const JobPost &Job) const = 0;
};

class JobSeeker : public IObserver
{
public:
	JobSeeker(const std::string &Name)
		: Name{ Name }
	{
	}

	virtual void OnJobPosted(const JobPost &Job) const override
	{
		std::cout << Name << " is seeking for job " << Job.GetTitle() << std::endl;
	}

private:
	std::string Name;
};

class IObservable
{
	virtual void Attach(IObserver &Observer) = 0;
	virtual void AddJob(const JobPost &JobPosting) = 0;
	virtual void Notify(const JobPost &JobPosting) = 0;
};

class JobPostings : public IObservable
{
public:
	void Attach(IObserver &Observer) override
	{
		Observers.push_back(Observer);
	}

	void AddJob(const JobPost &JobPostings) override
	{
		Notify(JobPostings);
	}

private:
	void Notify(const JobPost &JobPosting) override
	{
		for (IObserver &r : Observers)
		{
			r.OnJobPosted(JobPosting);
		}
	}

	std::vector<std::reference_wrapper<IObserver>> Observers;
};

int main()
{
	JobSeeker A("A"), B("B");

	JobPostings JobPostings_;
	JobPostings_.Attach(A);
	JobPostings_.Attach(B);

	JobPostings_.AddJob(JobPost("Software Engineer"));

	return 0;
}