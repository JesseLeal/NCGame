#include "StateMachine.h"

void StateMachine::Update()
{
	if (m_state)
	{
		m_state->Update();
	}
}

void StateMachine::AddState(const std::string & stateName, IState * state)
{
	assert(m_states.find(stateName) == m_states.end());

	m_states[stateName] = state;
}

void StateMachine::SetState(const std::string & key)
{
	if (m_states.find(key) != m_states.end())
	{
		IState* newState = m_states[key];
		if (newState != m_state)
		{
			if (m_state)
				m_state->Exit();

			m_state = newState;
			m_state->Enter();
			m_state->Update();//?
		}
	}
}